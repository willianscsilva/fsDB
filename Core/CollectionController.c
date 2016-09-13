#include "CollectionController.h"
#include "Str2Md5.h"
#include "../Default.h"
#include "cJSON.h"
#include "RegexController.h"
#include "ArrayController.h"

int foundDocuments;
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

int addDocumentInCollection(char* collection, char *id, const char *documentValue)
{
    int cmp = strcmp(collection, "");
    if(cmp!=0)
    {
        char *documentValueMd5 = 0;
        char *documentIdMd5 = 0;
        char *documentValueObj = 0;
        char *dir = pathCollection__(collection);

        documentValueMd5 = str2md5(documentValue, strlen(documentValue));
        documentIdMd5    = str2md5(id, strlen(id));
        documentValueObj = buildCollecionContent(documentValueMd5, documentIdMd5);
        strcat(documentValueObj, "\n");

        int add__ =  addInCollection__(dir, documentValueObj);
        if(add__ == 1)
        {
            addInDocument__(documentValueMd5, documentValue);
        }
        else
        {
            printf("Document already exists!\n");//tracking error here.
            return 0;
        }
        return 1;
    }
    else
    {
        printf("Collection name can be not empty!\n");//tracking error here.
        return 0;
    }
}

char *find(char* collection, char *id, char *query)
{
    char *documentIdMd5 = str2md5(id, strlen(id));
    find_readCollection(documentIdMd5, collection);
    (foundDocuments) ? find_readList(query) : NULL;
}

void find_readList(char *query)
{
    int i=0;    
    while(i<indexOfStrings)
    {
        find_execQueryInDocument(arrayOfStrings[i], query);
        i++;
    }
}

void find_execQueryInDocument(char *documentName, char *query)
{
    printf("Open this document: %s and execute this query: %s\n", documentName, query);

}

void find_readCollection(char *documentId, char* collection)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char * path = pathCollection__(collection);
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Trying read, but Collection not exists!\n");//tracking error here.
        return;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        find_documentsById(line, documentId);
    }
    fclose(fp);
    if (line)
    {
        free(line);
    }
}

void find_documentsById(char *lineContent_collection, char *documentId)
{
    int match;
    char *patternFormat = "{\"(.*?)\":{\"id\":\"%s\"}}";
    int length = strlen(patternFormat) + strlen(documentId);
    char pattern[length];
    sprintf(pattern, patternFormat, documentId);
    match = regexMatch(pattern, lineContent_collection);
    if(match)
    {
        int exists = checkStringValueExistsArray(contentMatch);
        //printf("exists: %i\n", exists);
        if(exists == 0)
        {
            appendStringArray(contentMatch);
            foundDocuments = 1;
        }
    }
    contentMatch = NULL;
}

char *buildCollecionContent(char *documentName, char *documentId)
{
    cJSON *root,*id;
    root = cJSON_CreateObject();
    cJSON_AddItemToObject(root, documentName, id = cJSON_CreateObject());
    cJSON_AddStringToObject(id, "id", documentId);
    char * rendered = cJSON_PrintUnformatted(root);
    return rendered;
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
        //improve this comparison method
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
