//
// SQLiteDatabaseHelperTest
// Source/Entry.c
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <SQLiteDatabaseHelper.h>

#define QUERY_NAME_MAX 256
#define QUERY_STATEMENT_MAX 256
#define ALL_ARTIST_QUERY "SELECT * FROM Artist"
#define RUSH_ARTIST_QUERY "SELECT * FROM Artist WHERE Name='Rush'"

char *removeTrailingNewline
(
    char *pString
);

void printQueryResult
(
    SQLiteQueryResult *pQueryResult
);

int main(int argc, const char **argv)
{
    // bool bExit = false;
    DatabaseReader *pDatabaseReader = NULL;
    
    char *pQueryName = NULL;
    char *pQueryStatement = NULL;
    
    if (2 > argc)
    {
        printf("Usage: '<PATH_TO_DATABASE>'\n");
        
        return 1;
    }
    
    pDatabaseReader = createDatabaseReader(*(argv + 1));
    
    pQueryName      = (char *) malloc(sizeof(char) * QUERY_NAME_MAX);
    pQueryStatement = (char *) malloc(sizeof(char) * QUERY_STATEMENT_MAX);
    
    if (NULL == pQueryName || NULL == pQueryStatement)
        return 1;
    
    // XXX: BAD HACK
    pDatabaseReader->registerQuery(pDatabaseReader, "All Artists",
        ALL_ARTIST_QUERY);
    pDatabaseReader->registerQuery(pDatabaseReader, "Rush", RUSH_ARTIST_QUERY);
    
    pDatabaseReader->executeQueries(pDatabaseReader);
    
    printf("All Artists\n");
    printQueryResult(pDatabaseReader->getQueryResults(pDatabaseReader,
        "All Artists"));
    
    printf("Rush\n");
    printQueryResult(pDatabaseReader->getQueryResults(pDatabaseReader, "Rush"));
    // XXXXXXXXXXXXX
    
    // while (!bExit)
    // {
    //     SQLiteQueryResult *pQueryResult = NULL;
    
    //     printf("Please enter a query name (%d characters max): ",
    //         (QUERY_NAME_MAX - 1));
    //     fgets(pQueryName, QUERY_NAME_MAX, stdin);
    //     removeTrailingNewline(pQueryName);
    
    //     printf("Please enter a query (%d characters max): ",
    //         (QUERY_STATEMENT_MAX - 1));
    //     fgets(pQueryStatement, QUERY_STATEMENT_MAX, stdin);
    //     removeTrailingNewline(pQueryStatement);
    
    //     if (!strlen(pQueryName) || !strlen(pQueryStatement))
    //     {
    //         bExit = true;
    //         break;
    //     }
    
    //     printf("%s : %s\n", pQueryName, pQueryStatement);
    
    //     pDatabaseReader->registerQuery(pDatabaseReader, pQueryName,
    //         pQueryStatement);
    //     pDatabaseReader->executeQuery(pDatabaseReader, pQueryName);
    //     pQueryResult = pDatabaseReader->getQueryResults(pDatabaseReader,
    //         pQueryName);
    
    //     if (NULL == pQueryResult)
    //         printf("Query has no results\n");
    //     else
    //     {
    //         printQueryResult(pQueryResult);
    //     }
    // }
    
    free(pQueryName);
    free(pQueryStatement);
    
    destroyDatabaseReader(pDatabaseReader);
    
    return 0;
}

char *removeTrailingNewline
(
    char *pString
)
{
    int stringLength = 0;
    
    if (NULL == pString)
        return NULL;
    
    stringLength = strlen(pString);
    
    if (0 < stringLength && '\n' == *(pString + (stringLength - 1)))
        *(pString + (stringLength - 1)) = '\0';
    
    return pString;
}

void printQueryResult
(
    SQLiteQueryResult *pQueryResult
)
{
    if (NULL == pQueryResult)
        return;
    
    printf("%d row(s) found with %d column(s) each\n", pQueryResult->rowCount,
        pQueryResult->colCount);
    
    // Print table header
    for (int headIndex = 0; headIndex < pQueryResult->colCount; ++headIndex)
    {
        printf("| %12s ", pQueryResult->getColumnName(pQueryResult, headIndex));
    }
    printf("|\n");
    
    // Print rows
    for (int rowIndex = 0; rowIndex < pQueryResult->rowCount; ++rowIndex)
    {
        for (int colIndex = 0; colIndex < pQueryResult->colCount; ++colIndex)
        {
            printf("| %12s ", pQueryResult->getColumnValue(pQueryResult, rowIndex,
                pQueryResult->getColumnName(pQueryResult, colIndex)));
        }
        
        printf("|\n");
    }
}