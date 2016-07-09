//
// SQLiteDatabaseHelper
// Include/DataStructures/KeyValue/KeyValuePairContainer.h
//
#ifndef __SQLITEDATABASEHELPER_DATASTRUCTURES_KEYVALUEPAIRCONTAINER_H__
#define __SQLITEDATABASEHELPER_DATASTRUCTURES_KEYVALUEPAIRCONTAINER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "DataStructures/KeyValue/KeyValuePair.h"

#define KEY_VALUE_PAIR_OK        0x0
#define KEY_VALUE_PAIR_ERROR     0x1
#define KEY_VALUE_PAIR_EXISTS    0x2
#define KEY_VALUE_PAIR_NOT_FOUND 0x3

// A Key-Value Pair (KVP) container will be represented as a pointer to an
//  instance of the 'keyValuePairContainer' struct.
//
// The 'keyValuePairContainer' struct can be thought of as an object, with the
//  'createKVPContainer()' function acting as the constructor, and the
//  'destroyKVPContainer()' function acting as the destructor.
//
// The 'keyValuePairContainer' struct will be used to store each of the KVPs,
//  as well as pointers to functions to help "maintain" said KVPs.
//
// KVPs will be represented using an array of pointers to the 'KeyValuePair'
//  type (see 'DataStructures/KeyValue/KeyValuePair.h'). The aforementioned
//  array will be accessible via the 'ppKeyValuePairs' attribute contained
//  within the 'keyValuePairContainer' struct.
//
// The total number of Key-Value Pairs that're stored in an instance of the
//  'keyValuePairContainer' struct, will be recorded in the 'numberOfPairs'
//  attribute.
//
// TODO: Function to create and add a new Key-Value pair
// TODO: Function to check to see if a Key-Value pair exists with desired key
// TODO: Function to get the value from a Key-Value pair with a certain key
// TODO: Function to get a list of all of the keys in the container
// TODO: Function to make sure a key is unique
struct keyValuePairContainer; // Forward-Declaration
struct keyValuePairContainer  // Definition
{
    int numberOfPairs;
    KeyValuePair **ppKeyValuePairs;
    
    int (*add)
    (
        struct keyValuePairContainer *pContainer,
        const char *pKey,
        void *pValue,
        size_t valueSize
    );
    
    KeyValuePair *(*get)
    (
        struct keyValuePairContainer *pContainer,
        const char *pKey
    );
};

// To remove some of the overhead involved in declaring a new instance of the
//  'keyValuePairContainer' struct, we'll perform a typedef operation, thus
//  allowing us to declare instances of the struct without having to type as much.
typedef struct keyValuePairContainer KVPContainer;

KVPContainer *createKVPContainer();

void destroyKVPContainer
(
    KVPContainer *pContainer // IN: The Key-Value Pair container to be destroyed
);

int keyValuePairContainer_add
(
    KVPContainer *pContainer,
    const char *pKey, // IN: The Key-Value Pair's key
    void *pValue,     // IN: Pointer to the Key-Value Pair's value
    size_t valueSize  // IN: The size (in bytes) of the Key-Value Pair's value
);

KeyValuePair *keyValuePairContainer_get
(
    KVPContainer *pContainer,
    const char *pKey // IN: The key of the desired Key-Value Pair
);

#endif