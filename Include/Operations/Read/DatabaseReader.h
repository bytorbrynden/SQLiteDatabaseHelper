//
// SQLiteDatabaseHelper
// Include/SQLiteDatabaseHelper/Operations/Read/DatabaseReader.h
//
#ifndef __SQLITEDATABASEHELPER_DATABASEREADER_H__
#define __SQLITEDATABASEHELPER_DATABASEREADER_H__

#include <stdio.h>

#include <sqlite3/sqlite3.h>

#include "SQLiteDatabaseHelperMacros.h"
#include "DataStructures/KeyValue/KeyValuePairContainer.h"
#include "DataStructures/SQLiteQueryResult/SQLiteQueryResult.h"

#define DATABASE_READER_OK              0x00
#define DATABASE_READER_ERROR           0x01
#define DATABASE_READER_QUERY_EXISTS    0x02
#define DATABASE_READER_QUERY_NOTEXISTS 0x03

// The 'databaseReader' struct can be thought of as the container that holds all
//  of the logic related to reading a database.
//
// As with other structs in this project, it is treated as an object, and has a
//  function that acts as its constructor ('createDatabaseReader()'), as well as
//  a function that acts as its destructor ('destroyDatabaseReader()').
struct databaseReader; // Forward-Declaration
struct databaseReader  // Definition
{
    // A pointer to an instance of the 'sqlite3' struct (see
    //  'Libraries/sqlite3/sqlite3.h'). This will be used to manage whatever
    //  sqlite database is opened.
    sqlite3 *pDatabase;
    
    int sqlite3_status_code;
    
    // This, which is stored for reference only, is the path to the database
    //  file specified by the consumer of this library.
    const char *pDatabaseFilePath;
    
    // Each query that is registered with the database reader, will be stored as
    //  a Key-Value Pair, with the key being the name of the query, and the
    //  value being the actual query statement.
    KVPContainer *pRegisteredQueries;
    
    KVPContainer *pQueryResults;
    
    int (*registerQuery)
    (
        struct databaseReader *pDatabaseReader,
        const char *pQueryName,
        char *pQueryStatement
    );
    
    int (*executeQuery)
    (
        struct databaseReader *pDatabaseReader,
        const char *pQueryName
    );
    
    void (*executeQueries)
    (
        struct databaseReader *pDatabaseReader
    );
    
    int (*setResultColumns)
    (
        struct databaseReader *pDatabaseReader,
        sqlite3_stmt *pSQLStatement,
        SQLiteQueryResult *pQueryResult
    );
    
    int (*setResultRows)
    (
        struct databaseReader *pDatabaseReader,
        sqlite3_stmt *pSQLStatement,
        SQLiteQueryResult *pQueryResult
    );
    
    SQLiteQueryResult *(*getQueryResults)
    (
        struct databaseReader *pDatabaseReader,
        const char *pQueryName
    );
};

typedef struct databaseReader DatabaseReader;

C_FUNC_BLOCK_START // Begin C-linkage block

EXPORT_FUNC DatabaseReader *createDatabaseReader
(
    const char *pDatabaseFilePath
);

EXPORT_FUNC void destroyDatabaseReader
(
    DatabaseReader *pDatabaseReader
);

EXPORT_FUNC int databaseReader_registerQuery
(
    DatabaseReader *pDatabaseReader,
    const char *pQueryName,
    char *pQueryStatement
);

EXPORT_FUNC int databaseReader_executeQuery
(
    DatabaseReader *pDatabaseReader,
    const char *pQueryName
);

EXPORT_FUNC void databaseReader_executeQueries
(
    DatabaseReader *pDatabaseReader
);

EXPORT_FUNC void databaseReader_queryResultDestroyer
(
    void *pQueryResult
);

EXPORT_FUNC int databaseReader_setResultColumns
(
    DatabaseReader *pDatabaseReader,
    sqlite3_stmt *pSQLStatement,
    SQLiteQueryResult *pQueryResult
);

EXPORT_FUNC int databaseReader_setResultRows
(
    DatabaseReader *pDatabaseReader,
    sqlite3_stmt *pSQLStatement,
    SQLiteQueryResult *pQueryResult
);

EXPORT_FUNC SQLiteQueryResult *databaseReader_getQueryResults
(
    DatabaseReader *pDatabaseReader,
    const char *pQueryName
);

C_FUNC_BLOCK_END // End C-linkage block

#endif