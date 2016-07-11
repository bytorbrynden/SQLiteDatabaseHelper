//
// SQLiteDatabaseHelper
// Source/DataStructures/KeyValue/KeyValuePairContainer.c
//
#include <SQLiteDatabaseHelper/DataStructures/KeyValue/KeyValuePairContainer.h>

KVPContainer *createKVPContainer()
{
    KVPContainer *pContainer = (KVPContainer *) malloc(sizeof(KVPContainer));
    
    // A Key-Value Pair container will always start out with 0 Key-Value Pairs
    //  allocated. It will be up to the consumer of this code to allocate and
    //  add pairs to the container.
    
    pContainer->numberOfPairs   = 0;
    pContainer->ppKeyValuePairs = (KeyValuePair **) malloc(0);
    
    pContainer->add  = keyValuePairContainer_add;
    pContainer->get  = keyValuePairContainer_get;
    pContainer->list = keyValuePairContainer_list;
    
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

int keyValuePairContainer_add
(
    KVPContainer *pContainer,
    const char *pKey,
    void *pValue,
    size_t valueSize
)
{
    if (NULL == pContainer || NULL == pKey || NULL == pValue)
        return KEY_VALUE_PAIR_ERROR;
    
    // Check to make sure a pair with the specified key doesn't already exist
    if (NULL != pContainer->get(pContainer, pKey))
        return KEY_VALUE_PAIR_EXISTS;
    
    // Increase the size of the array of Key-Value Pairs
    pContainer->ppKeyValuePairs = (KeyValuePair **) realloc(
        pContainer->ppKeyValuePairs,
        (sizeof(KeyValuePair) * (pContainer->numberOfPairs + 1))
    );
    
    // Create the new Key-Value Pair
    *(pContainer->ppKeyValuePairs + pContainer->numberOfPairs) = (
        createKeyValuePair(pKey, pValue, valueSize)
    );
    
    // Increase the total number of pairs stored in the container
    pContainer->numberOfPairs++;
    
    return KEY_VALUE_PAIR_OK;
}

KeyValuePair *keyValuePairContainer_get
(
    KVPContainer *pContainer,
    const char *pKey
)
{
    if (NULL == pContainer || NULL == pKey)
        return NULL;
    
    for (int pairIndex = 0; pairIndex < pContainer->numberOfPairs; ++pairIndex)
    {
        KeyValuePair *pCurrentPair = *(pContainer->ppKeyValuePairs + pairIndex);
        
        if (!strncmp(pKey, pCurrentPair->pKey, strlen(pKey)))
            return pCurrentPair;
    }
    
    return NULL;
}

char **keyValuePairContainer_list
(
    KVPContainer *pContainer
)
{
    char **ppPairKeys = NULL;
    
    if (NULL == pContainer)
        return NULL;
    
    ppPairKeys = (char **) malloc(sizeof(char *) * pContainer->numberOfPairs);
    
    for (int pairIndex = 0; pairIndex < pContainer->numberOfPairs; ++pairIndex)
    {
        KeyValuePair *pCurrentPair = *(pContainer->ppKeyValuePairs);
        
        *(ppPairKeys + pairIndex) = (char *) pCurrentPair->pKey;
    }
    
    return ppPairKeys;
}