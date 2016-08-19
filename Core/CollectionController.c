#include "CollectionController.h"
#include "Str2Md5.h"
#include "../Default.h"

char *pathCollection__(const char *collectionName)
{
    static char dir[50];
    strcpy(dir, "collections/");
    strcat(dir, collectionName);
    return dir;
}

int createCollection(const char *collectionName)
{
    int collectionExists;
    int collectionCreated=0;
    char *dir = pathCollection__(collectionName);

    collectionExists = checkCollectionExists(dir);
    if(!collectionExists)
    {

        FILE * fp;
        fp = fopen( dir, "w" );
        if(fp != NULL)
        {
            collectionCreated = 1;
        }
        fclose(fp);
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
        fclose(fp);
    }
    return exists;
}

int addDocumentInCollection(char* name, const char *documentValue)
{
    int cmp = strcmp(name, "");
    if(cmp!=0)
    {
        char *outMd5 = 0;
        char *dir = pathCollection__(name);

        outMd5 = str2md5(documentValue, strlen(documentValue));
        strcat(outMd5, "\n");
        int add__ =  addInCollection__(dir, outMd5);
        if(add__ == 1)
        {
            addInDocument__(outMd5, documentValue);
        }
        else
        {
            printf("Document already exists!\n");//tracking error here.
        }
        return 1;
    }
    else
    {
        printf("Collection name can be not empty!\n");//tracking error here.
        return 0;
    }
}

int checkDocumentExists(char *pathCollection, char *documentName)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(pathCollection, "r");
    if (fp == NULL)
    {
        printf("Collection not exists!\n");//tracking error here.
        return 0;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        if(strcmp(line, documentName) == 0)
        {
            return 1;
        }
    }

    fclose(fp);
    if (line)
    {
        free(line);
    }
    return 0;
}

int addInCollection__(char *path, char *value)
{
    int docExists = checkDocumentExists(path, value);
    if(docExists == 0)
    {
        write__(path, value, "a+");
        return 1;
    }
    return 0;
}

void addInDocument__(char *documentName, const char *value)
{
    char *dir = pathCollection__(documentName);
    register int len = strlen(dir);
    register int i;
    //remove \n from string
    for(i = 0; i < len; i++)
    {
        if(dir[i] == '\n')
        {
            dir[i] = '\0';
        }
    }
    write__(dir, (char*)value, "w");
}

void write__(char *path, char *value, const char * type)
{
    FILE * fp;
    fp = fopen( path, type );
    fwrite(value , 1 , strlen(value) , fp );
    fclose(fp);
}
