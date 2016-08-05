#include "CollectionController.h"

int createCollection(const char *collectionName)
{
    int collectionExists;
    int collectionCreated;
    collectionExists = checkCollectionExists(collectionName);
    if(!collectionExists)
    {
        FILE * fp;
        fp = fopen( collectionName, "w" );
        if(fp != NULL)
        {
            collectionCreated = 1;
        }
        else
        {
            collectionCreated = 0;
        }
        fclose(fp);
    }
    else
    {
        collectionCreated = 0;
    }
    return collectionCreated;
}

int checkCollectionExists(const char *collectionName)
{
    FILE * fp;
    fp = fopen( collectionName, "r" );
    if(fp != NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int addDocumentInCollection(const char *collectionName){

}
