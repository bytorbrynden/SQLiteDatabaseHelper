//
// SQLiteDatabaseHelper
// Source/DataStructures/KeyValue/KeyValuePairContainer.c
//
#include "DataStructures/KeyValue/KeyValuePairContainer.h"

KVPContainer *createKVPContainer()
{
    KVPContainer *pContainer = (KVPContainer *) malloc(sizeof(KVPContainer));
    
    // A Key-Value Pair container will always start out with 0 Key-Value Pairs
    //  allocated. It will be up to the consumer of this code to allocate and
    //  add pairs to the container.
    
    pContainer->numberOfPairs   = 0;
    pContainer->ppKeyValuePairs = (KeyValuePair **) malloc(0);
    
    return pContainer;
}

void destroyKVPContainer
(
    KVPContainer *pContainer
)
{
    // If the pointer to the 'KVPContainer' that is passed to us, is 'NULL', we
    //  have nothing to deallocate, so we'll exit the function.
    if (NULL == pContainer)
        return;
    
    if (NULL != pContainer->ppKeyValuePairs)
    {
        for (int i = 0; i < pContainer->numberOfPairs; ++i)
            destroyKeyValuePair(*(pContainer->ppKeyValuePairs + i));
        
        free(pContainer->ppKeyValuePairs);
    }
    
    free(pContainer);
}