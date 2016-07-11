//
// SQLiteDatabaseHelper
// Source/Operations/Read/DatabaseReader.c
//
#include <SQLiteDatabaseHelper/Operations/Read/DatabaseReader.h>

DatabaseReader *createDatabaseReader
(
    const char *pDatabaseFilePath
)
{
    DatabaseReader *pReader = NULL;
    
    if (NULL == pDatabaseFilePath)
        return NULL;
    
    pReader = (DatabaseReader *) malloc(sizeof(DatabaseReader));
    
    pReader->pDatabaseFilePath   = pDatabaseFilePath;
    pReader->sqlite3_status_code = sqlite3_open(pDatabaseFilePath,
        &pReader->pDatabase);
    pReader->pRegisteredQueries  = createKVPContainer();
    pReader->pQueryResults       = createKVPContainer();
    
    pReader->registerQuery    = databaseReader_registerQuery;
    pReader->executeQuery     = databaseReader_executeQuery;
    pReader->setResultColumns = databaseReader_setResultColumns;
    pReader->setResultRows    = databaseReader_setResultRows;
    pReader->getQueryResults  = databaseReader_getQueryResults;
    
    return pReader;
}

void destroyDatabaseReader
(
    DatabaseReader *pDatabaseReader
)
{
    if (NULL == pDatabaseReader)
        return;
    
    if (NULL != pDatabaseReader->pDatabase)
        sqlite3_close(pDatabaseReader->pDatabase);
    
    if (NULL != pDatabaseReader->pRegisteredQueries)
        destroyKVPContainer(pDatabaseReader->pRegisteredQueries);
    
    if (NULL != pDatabaseReader->pQueryResults)
    {
        char **ppQueryResults = pDatabaseReader->pQueryResults->list(
            pDatabaseReader->pQueryResults);
        
        for (int i = 0; i < pDatabaseReader->pQueryResults->numberOfPairs; ++i)
        {
            KeyValuePair *pPair = pDatabaseReader->pQueryResults->get(
                pDatabaseReader->pQueryResults, *(ppQueryResults + i));
            
            SQLiteQueryResult *pQueryResult = (
                (SQLiteQueryResult *) pPair->pValue
            );
            
            destroySQLiteQueryResult(pQueryResult);
            
            free(pPair);
        }
        
        // destroyKVPContainer(pDatabaseReader->pQueryResults);
        free(ppQueryResults);
        free(pDatabaseReader->pQueryResults->ppKeyValuePairs);
        free(pDatabaseReader->pQueryResults);
    }
    
    free(pDatabaseReader);
}

int databaseReader_registerQuery
(
    DatabaseReader *pDatabaseReader,
    const char *pQueryName,
    char *pQueryStatement
)
{
    int pairAddStatus = -1;
    
    if (NULL == pDatabaseReader || NULL == pDatabaseReader->pRegisteredQueries)
        return DATABASE_READER_ERROR;
    
    pairAddStatus = pDatabaseReader->pRegisteredQueries->add(
        pDatabaseReader->pRegisteredQueries, pQueryName, pQueryStatement,
        (sizeof(char) * (strlen(pQueryStatement) + 1))
    );
    
    if (KEY_VALUE_PAIR_EXISTS == pairAddStatus)
        return DATABASE_READER_QUERY_EXISTS;
    
    return DATABASE_READER_OK;
}

int databaseReader_executeQuery
(
    DatabaseReader *pDatabaseReader,
    const char *pQueryName
)
{
    bool bHasQuery = false;
    char *pQuery   = NULL;
    
    sqlite3_stmt *pSQLStatement = NULL;
    
    SQLiteQueryResult *pQueryResult = NULL;
    
    if (NULL == pDatabaseReader || NULL == pQueryName)
        return DATABASE_READER_ERROR;
    
    bHasQuery = pDatabaseReader->pRegisteredQueries->hasKey(
        pDatabaseReader->pRegisteredQueries, pQueryName);
    
    if (!bHasQuery)
        return DATABASE_READER_QUERY_NOTEXISTS;
    
    pQuery = (char *) pDatabaseReader->pRegisteredQueries->get(
        pDatabaseReader->pRegisteredQueries, pQueryName)->pValue;
    
    pQueryResult = createSQLiteQueryResult();
    
    if (SQLITE_OK == sqlite3_prepare_v2(pDatabaseReader->pDatabase, pQuery, -1,
        &pSQLStatement, 0))
    {
        int setupColumnsStatus = pDatabaseReader->setResultColumns(
            pDatabaseReader, pSQLStatement, pQueryResult);
        
        if (DATABASE_READER_OK == setupColumnsStatus)
        {
            int setupRowsStatus = pDatabaseReader->setResultRows(pDatabaseReader,
                pSQLStatement, pQueryResult);
            
            if (DATABASE_READER_OK == setupRowsStatus)
            {
                pDatabaseReader->pQueryResults->add(
                    pDatabaseReader->pQueryResults, pQueryName, pQueryResult,
                    sizeof(SQLiteQueryResult));
                
                free(pQueryResult);
            }
        }
        
        sqlite3_finalize(pSQLStatement);
    }
    
    return DATABASE_READER_OK;
}

int databaseReader_setResultColumns
(
    DatabaseReader *pDatabaseReader,
    sqlite3_stmt *pSQLStatement,
    SQLiteQueryResult *pQueryResult
)
{
    int columnCount = 0;
    
    if (NULL == pDatabaseReader || NULL == pSQLStatement || NULL == pQueryResult)
        return DATABASE_READER_ERROR;
    
    columnCount = sqlite3_column_count(pSQLStatement);
    
    for (int columnIndex = 0; columnIndex < columnCount; ++columnIndex)
    {
        char *pColumnName = (char *) sqlite3_column_name(pSQLStatement,
            columnIndex);
        
        // TODO: Get actual sqlite column types
        pQueryResult->registerColumn(pQueryResult, 0, pColumnName);
    }
    
    return DATABASE_READER_OK;
}

int databaseReader_setResultRows
(
    DatabaseReader *pDatabaseReader,
    sqlite3_stmt *pSQLStatement,
    SQLiteQueryResult *pQueryResult
)
{
    int row = 0;
    
    if (NULL == pDatabaseReader || NULL == pSQLStatement || NULL == pQueryResult)
        return DATABASE_READER_ERROR;
    
    while (SQLITE_ROW == sqlite3_step(pSQLStatement))
    {
        pQueryResult->allocateRow(pQueryResult);
        
        for (int column = 0; column < pQueryResult->colCount; ++column)
        {
            char *pValue = (char *) sqlite3_column_text(pSQLStatement, column);
            pValue = (NULL == pValue ? "" : pValue);
            
            pQueryResult->setRowColumnValue(pQueryResult, row, column, pValue);
        }
        
        row++;
    }
    
    return DATABASE_READER_OK;
}

SQLiteQueryResult *databaseReader_getQueryResults
(
    DatabaseReader *pDatabaseReader,
    const char *pQueryName
)
{
    if (NULL == pDatabaseReader || NULL == pQueryName)
        return NULL;
    
    if (!pDatabaseReader->pQueryResults->hasKey(pDatabaseReader->pQueryResults,
        pQueryName))
        return NULL;
    
    return (SQLiteQueryResult *) pDatabaseReader->pQueryResults->get(
        pDatabaseReader->pQueryResults, pQueryName)->pValue;
}