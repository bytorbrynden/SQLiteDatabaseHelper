//
// SQLiteDatabaseHelper
// Source/DataStructures/KeyValue/KeyValuePair.c
//
#include <SQLiteDatabaseHelper/DataStructures/KeyValue/KeyValuePair.h>

KeyValuePair *createKeyValuePair
(
    const char *pKey,
    void *pValue,
    size_t valueSize
)
{
    KeyValuePair *pNewPair = NULL;
    
    // If either the key or the pointer to the value are 'NULL', we won't
    //  create a new instance of the 'KeyValuePair' struct. Instead, we'll
    //  return from the function early.
    if (NULL == pKey || NULL == pValue)
        return pNewPair;
    
    pNewPair = (KeyValuePair *) malloc(sizeof(KeyValuePair));
    
    pNewPair->pKey   = pKey;
    pNewPair->pValue = malloc(valueSize);
    
    memcpy(((unsigned char *) pNewPair->pValue), pValue, valueSize);
    
    return pNewPair;
}

void destroyKeyValuePair
(
    KeyValuePair *pPair
)
{
    // If the pointer to the pair that was passed is 'NULL', there's nothing to
    //  deallocate, so we'll exit the function.
    if (NULL == pPair)
        return;
    
    if (NULL != pPair->pValue)
        free(pPair->pValue);
    
    free(pPair);
}