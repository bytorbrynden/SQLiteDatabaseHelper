//
// SQLiteDatabaseHelper
// Include/DataStructures/KeyValue/KeyValuePair.h
//
#ifndef __SQLITEDATABASEHELPER_DATASTRUCTURES_KEYVALUEPAIR_H__
#define __SQLITEDATABASEHELPER_DATASTRUCTURES_KEYVALUEPAIR_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A Key-Value Pair is often described as follows:
//      "A key-value pair (KVP) is a set of two linked data items: a key, which
//      is a unique identifier for some item of data, and the value, which is
//      either the data that is identified or a pointer to the location of that
//      data"
// We'll represent Key-Value Pairs using a struct, named 'keyValuePair'
//  respectively.
//
// The 'keyValuePair' struct, will consist of the following:
//  - A C-string representing the pair's "key" ('pKey' attribute)
//  - A generic type pointing to the pair's "value" ('pValue' attribute)
//
// The 'createKeyValuePair()' function will act as the constructor for our
//  "object". It will be tasked with allocating any and all memory that is to
//  be used for the Key-Value Pair.
// The 'destroyKeyValuePair()' function will act as the destructor, deallocating
//  any memory that was previously allocated for the Key-Value Pair.
struct keyValuePair; // Forward-Declaration
struct keyValuePair  // Definition
{
    const char *pKey;
    void *pValue;
};

// As was done with the 'keyValuePairContainer' struct
//  (see 'DataStructures/KeyValue/KeyValuePairContainer.h'), we'll perform a
//  typedef operation to reduce some of the overhead involved with declaring a
//  new instance of the 'keyValuePair' struct.
typedef struct keyValuePair KeyValuePair;

// The 'createKeyValuePair()' function acts as a constructor for the
//  'keyValuePair' struct. It is tasked with allocating any memory that is
//  required for a Key-Value Pair.
KeyValuePair *createKeyValuePair
(
    const char *pKey, // IN: The key for the new pair.
    void *pValue      // IN: A pointer to the value for the new pair.
);

// The 'destroyKeyValuePair()' function acts as the destructor for the
//  'keyValuePair' struct. It attempts to deallocate all of the memory that was
//  allocated for use with the Key-Value pair.
void destroyKeyValuePair
(
    KeyValuePair *pPair // IN: A pointer to the Key-Value pair to be destroyed.
);

#endif