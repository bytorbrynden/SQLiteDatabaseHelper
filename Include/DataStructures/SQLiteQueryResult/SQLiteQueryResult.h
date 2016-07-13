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

#include "SQLiteDatabaseHelperMacros.h"

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

C_FUNC_BLOCK_START // Begin C-linkage block

EXPORT_FUNC SQLiteQueryResult *createSQLiteQueryResult();

EXPORT_FUNC void destroySQLiteQueryResult
(
    SQLiteQueryResult *pQueryResult
);

EXPORT_FUNC void sqliteQueryResult_registerColumn
(
    SQLiteQueryResult *pQueryResult,
    int sqliteType,
    char *pColumnName
);

EXPORT_FUNC void sqliteQueryResult_allocateRow
(
    SQLiteQueryResult *pQueryResult
);

EXPORT_FUNC void sqliteQueryResult_setRowColumnValue
(
    SQLiteQueryResult *pQueryResult,
    int rowIndex,
    int colIndex,
    char *pValue
);

EXPORT_FUNC int sqliteQueryResult_getColumnIndex
(
    SQLiteQueryResult *pQueryResult,
    char *pColumnName
);

EXPORT_FUNC char *sqliteQueryResult_getColumnName
(
    SQLiteQueryResult *pQueryResult,
    int columnIndex
);

EXPORT_FUNC char *sqliteQueryResult_getColumnValue
(
    SQLiteQueryResult *pQueryResult,
    int rowIndex,
    char *pColumnName
);

C_FUNC_BLOCK_END // End C-linkage block

#endif