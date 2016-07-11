//
// SQLiteDatabaseHelper
// Source/DataStructures/SQLiteQueryResult/SQLiteQueryResult.c
//
#include <SQLiteDatabaseHelper/DataStructures/SQLiteQueryResult/SQLiteQueryResult.h>

SQLiteQueryResult *createSQLiteQueryResult()
{
    SQLiteQueryResult *pQueryResult = (SQLiteQueryResult *) malloc(sizeof(
        SQLiteQueryResult));
    
    pQueryResult->colCount      = 0;
    pQueryResult->rowCount      = 0;
    pQueryResult->pColumnTypes  = (int *) malloc(0);
    pQueryResult->ppColumnNames = (char **) malloc(0);
    pQueryResult->pppRowValues  = (char ***) malloc(0);
    
    pQueryResult->registerColumn    = sqliteQueryResult_registerColumn;
    pQueryResult->allocateRow       = sqliteQueryResult_allocateRow;
    pQueryResult->setRowColumnValue = sqliteQueryResult_setRowColumnValue;
    pQueryResult->getColumnIndex    = sqliteQueryResult_getColumnIndex;
    pQueryResult->getColumnName     = sqliteQueryResult_getColumnName;
    pQueryResult->getColumnValue    = sqliteQueryResult_getColumnValue;
    
    return pQueryResult;
}

void destroySQLiteQueryResult
(
    SQLiteQueryResult *pQueryResult
)
{
    if (NULL == pQueryResult)
        return;
    
    if (NULL != pQueryResult->pColumnTypes)
        free(pQueryResult->pColumnTypes);
    
    if (NULL != pQueryResult->ppColumnNames)
    {
        for (int column = 0; column < pQueryResult->colCount; ++column)
        {
            if (NULL != *(pQueryResult->ppColumnNames + column))
                free(*(pQueryResult->ppColumnNames + column));
        }
        
        free(pQueryResult->ppColumnNames);
    }
    
    if (NULL != pQueryResult->pppRowValues)
    {
        for (int row = 0; row < pQueryResult->rowCount; ++row)
        {
            if (NULL == *(pQueryResult->pppRowValues + row))
                continue;
            
            for (int col = 0; col < pQueryResult->colCount; ++col)
            {
                if (NULL == *(*(pQueryResult->pppRowValues + row) + col))
                    continue;
                
                free(*(*(pQueryResult->pppRowValues + row) + col));
            }
            
            free(*(pQueryResult->pppRowValues + row));
        }
        
        free(pQueryResult->pppRowValues);
    }
    
    free(pQueryResult);
}

void sqliteQueryResult_registerColumn
(
    SQLiteQueryResult *pQueryResult,
    int sqliteType,
    char *pColumnName
)
{
    if (NULL == pQueryResult || NULL == pColumnName)
        return;
    
    // Step 0: Add column type to column types array
    pQueryResult->pColumnTypes = (int *) realloc(pQueryResult->pColumnTypes,
        (sizeof(int) * (pQueryResult->colCount + 1)));
    
    *(pQueryResult->pColumnTypes + pQueryResult->colCount) = sqliteType;
    
    // Step 1: Add column name to column names array
    pQueryResult->ppColumnNames = (char **) realloc(
        pQueryResult->ppColumnNames,
        (sizeof(char *) * (pQueryResult->colCount + 1))
    );
    
    *(pQueryResult->ppColumnNames + pQueryResult->colCount) = (
        (char *) malloc(sizeof(char) * (strlen(pColumnName) + 1))
    );
    
    strcpy(*(pQueryResult->ppColumnNames + pQueryResult->colCount),
        pColumnName);
    
    // Step 2: Increase total number of columns
    pQueryResult->colCount++;
}

void sqliteQueryResult_allocateRow
(
    SQLiteQueryResult *pQueryResult
)
{
    if (NULL == pQueryResult)
        return;
    
    /*
        {
            Row {
                Column Value {
                    'a'
                    'b'
                    'c'
                    '\0'
                }
            }
        }
     */
    
    pQueryResult->pppRowValues = (char ***) realloc(pQueryResult->pppRowValues,
        (sizeof(char **) * (pQueryResult->rowCount + 1)));
    *(pQueryResult->pppRowValues + pQueryResult->rowCount) = (char **) malloc(
        sizeof(char *) * pQueryResult->colCount);
    
    pQueryResult->rowCount++;
}

void sqliteQueryResult_setRowColumnValue
(
    SQLiteQueryResult *pQueryResult,
    int rowIndex,
    int colIndex,
    char *pValue
)
{
    if (NULL == pQueryResult)
        return;
    
    if ((0 > rowIndex || pQueryResult->rowCount <= rowIndex) ||
        (0 > colIndex || pQueryResult->colCount <= colIndex))
        return;
    
    if (NULL == *(pQueryResult->pppRowValues + rowIndex))
        return;
    
    *(*(pQueryResult->pppRowValues + rowIndex) + colIndex) = (char *) malloc(
        sizeof(char) * (strlen(pValue) + 1));
    
    strcpy(*(*(pQueryResult->pppRowValues + rowIndex) + colIndex), pValue);
}

int sqliteQueryResult_getColumnIndex
(
    SQLiteQueryResult *pQueryResult,
    char *pColumnName
)
{
    if (NULL == pQueryResult || NULL == pColumnName)
        return -1;
    
    for (int column = 0; column < pQueryResult->colCount; ++column)
    {
        char *pCurrentColumn = *(pQueryResult->ppColumnNames + column);
        
        if (!strncmp(pColumnName, pCurrentColumn, strlen(pColumnName)))
            return column;
    }
    
    return -1;
}

char *sqliteQueryResult_getColumnName
(
    SQLiteQueryResult *pQueryResult,
    int columnIndex
)
{
    if (NULL == pQueryResult)
        return NULL;
    
    if (0 > columnIndex || pQueryResult->colCount <= columnIndex)
        return NULL;
    
    return *(pQueryResult->ppColumnNames + columnIndex);
}

char *sqliteQueryResult_getColumnValue
(
    SQLiteQueryResult *pQueryResult,
    int rowIndex,
    char *pColumnName
)
{
    int columnIndex = 0;
    
    if (NULL == pQueryResult || NULL == pColumnName)
        return NULL;
    
    if (0 > rowIndex || pQueryResult->rowCount <= rowIndex)
        return NULL;
    
    if (0 > (columnIndex = pQueryResult->getColumnIndex(pQueryResult,
        pColumnName)))
        return NULL;
    
    return *(*(pQueryResult->pppRowValues + rowIndex) + columnIndex);
}