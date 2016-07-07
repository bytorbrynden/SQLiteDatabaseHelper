//
// SQLiteDatabaseHelper
// Include/DataStructures/KeyValue/KeyValuePairContainer.h
//
#ifndef __SQLITEDATABASEHELPER_DATASTRUCTURES_KEYVALUEPAIRCONTAINER_H__
#define __SQLITEDATABASEHELPER_DATASTRUCTURES_KEYVALUEPAIRCONTAINER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "DataStructures/KeyValue/KeyValuePair.h"

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
struct keyValuePairContainer; // Forward-Declaration
struct keyValuePairContainer  // Definition
{
    KeyValuePair **ppKeyValuePairs;
};

// To remove some of the overhead involved in declaring a new instance of the
//  'keyValuePairContainer' struct, we'll perform a typedef operation, thus
//  allowing us to declare instances of the struct without having to type as much.
typedef struct keyValuePairContainer KVPContainer;

KVPContainer *createKVPContainer();

void destroyKVPContainer
(
    KVPContainer *pContainer
);

#endif