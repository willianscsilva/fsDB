#include "CollectionController.h"

int createCollection(const char *collectionName)
{
    int collectionExists;
    int collectionCreated;
    char dir[50];
    memset(dir, '\0', sizeof(dir));
    strcpy(dir, "collections/");
    strcat(dir, collectionName);

    collectionExists = checkCollectionExists(dir);
    if(!collectionExists)
    {

        FILE * fp;
        fp = fopen( dir, "w" );
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
    int exists=0;
    FILE * fp;
    fp = fopen( collectionName, "r" );
    if(fp != NULL)
    {
        exists = 1;
    }
    fclose(fp);
    return exists;
}

int addDocumentInCollection(char* name, const char *documentValue)
{

    int cmp = strcmp(name, "");
    if(cmp!=0)
    {
        char dir[50];
        memset(dir, '\0', sizeof(dir));
        strcpy(dir, "collections/");
        strcat(dir, name);
        strcat((char *)documentValue, "\n");
        FILE * fp;
        fp = fopen( dir, "a+" );
        fwrite(documentValue , 1 , strlen(documentValue) , fp );
        fclose(fp);
        return 1;
    }
    else
    {
        printf("Collection name can be not empty!\n");
    }

}
