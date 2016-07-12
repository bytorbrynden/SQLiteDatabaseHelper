//
// SQLiteDatabaseHelper
// Include/SQLiteDatabaseHelper/DataStructures/SQLiteQueryResult/SQLiteQueryResult.h
//
#ifndef __SQLITEDATABASEHELPER_DATASTRUCTURES_SQLITEQUERYRESULT_H__
#define __SQLITEDATABASEHELPER_DATASTRUCTURES_SQLITEQUERYRESULT_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct sqliteQueryResult; // Forward-Declaration
struct sqliteQueryResult  // Definition
{
    int colCount;
    int rowCount;
    
    int *pColumnTypes;
    char **ppColumnNames;
    char ***pppRowValues;
    
    void (*registerColumn)
    (
        struct sqliteQueryResult *pQueryResult,
        int sqliteType,
        char *pColumnName
    );
    
    void (*allocateRow)
    (
        struct sqliteQueryResult *pQueryResult
    );
    
    void (*setRowColumnValue)
    (
        struct sqliteQueryResult *pQueryResult,
        int rowIndex,
        int colIndex,
        char *pValue
    );
    
    int (*getColumnIndex)
    (
        struct sqliteQueryResult *pQueryResult,
        char *pColumnName
    );
    
    char *(*getColumnName)
    (
        struct sqliteQueryResult *pQueryResult,
        int columnIndex
    );
    
    char *(*getColumnValue)
    (
        struct sqliteQueryResult *pQueryResult,
        int rowIndex,
        char *pColumnName
    );
};

typedef struct sqliteQueryResult SQLiteQueryResult;

SQLiteQueryResult *createSQLiteQueryResult();

void destroySQLiteQueryResult
(
    SQLiteQueryResult *pQueryResult
);

void sqliteQueryResult_registerColumn
(
    SQLiteQueryResult *pQueryResult,
    int sqliteType,
    char *pColumnName
);

void sqliteQueryResult_allocateRow
(
    SQLiteQueryResult *pQueryResult
);

void sqliteQueryResult_setRowColumnValue
(
    SQLiteQueryResult *pQueryResult,
    int rowIndex,
    int colIndex,
    char *pValue
);

int sqliteQueryResult_getColumnIndex
(
    SQLiteQueryResult *pQueryResult,
    char *pColumnName
);

char *sqliteQueryResult_getColumnName
(
    SQLiteQueryResult *pQueryResult,
    int columnIndex
);

char *sqliteQueryResult_getColumnValue
(
    SQLiteQueryResult *pQueryResult,
    int rowIndex,
    char *pColumnName
);

#endif