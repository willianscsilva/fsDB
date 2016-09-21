#include "CollectionController.h"
#include "Str2Md5.h"
#include "../Default.h"
#include "cJSON.h"
#include "RegexController.h"
#include "ArrayController.h"
#include "StringAuxiliary.h"
#include "WsReturn.h"

int foundDocuments;
int indexArrayDocuments;
char **arrayDocuments;
char **wsArrayReturn;
char *pathCollectionDocument__(const char *collectionName, char *documentName)
{
    static char dir[50];
    strcpy(dir, "collections/");
    if(collectionName != NULL)
    {
         strcat(dir, collectionName);
    }
    else if(documentName != NULL)
    {
        strcat(dir, documentName);
    }
    return dir;
}

int createCollection(const char *collectionName)
{
    int collectionExists;
    int collectionCreated=0;
    char *dir = pathCollectionDocument__(collectionName, NULL);

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
        char *dir = pathCollectionDocument__(collection, NULL);

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
    while(i<=indexArrayDocuments)
    {
        find_execQueryInDocument(arrayDocuments[i], query);
        i++;
    }

    wsArrayReturn = arrayDocuments;
    arrayDocuments = NULL;
    nullingStringArray();
}

void find_execQueryInDocument(char *documentName, char *query)
{
    printf("Open this document: %s\n", documentName);

    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char *path = pathCollectionDocument__(NULL, documentName);
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Trying read, but Document not exists!\n");//tracking error here.
        return;
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
        find_execQuery(line, query);
    }
    fclose(fp);
    if (line)
    {
        free(line);
    }
}

void find_execQuery(char * line, char *query)
{
    printf("Document content: %s - execute this query: %s\n", line, query);
    int match=0;
    char *queryField;
    char *queryValue;
    char *fieldValue;
    char *pattern = "/(.*?)/";
    match = regexMatch(pattern, query);
    contentMatch = NULL;
    if(match)
    {
        match = 0;
        query = str_replace(query, "/", "");

        queryField = getQueryField(query);
        queryValue = getQueryValue(query);
        fieldValue = find_getFieldValue(queryField, line);

        match = regexMatch(queryValue, fieldValue);
        if(match)
        {
            printf("The content is founded: %s\n", line);
            //appendStringArray(line);
        }
        else
        {
            printf("The content not fouded by query: %s\n", query);
        }
    }
    else
    {
        queryField = getQueryField(query);
        queryValue = getQueryValue(query);
        fieldValue = find_getFieldValue(queryField, line);
        if(strcmp(queryValue, fieldValue) == 0)
        {
            printf("The content is founded: %s\n", line);
            //appendStringArray(line);
        }
        else
        {
            printf("The content not fouded by query: %s\n", query);
        }
    }
}

char *getQueryField(char *query)
{
    char *queryField;
    char *pattern;
    pattern = "{\"(.*?)\":";
    regexMatch(pattern, query);
    queryField = contentMatch;
    contentMatch = NULL;
    return queryField;
}

char *getQueryValue(char *query)
{
   char *queryValue;
   char *pattern;
   pattern = ":\"(.*?)\"}";
   regexMatch(pattern, query);
   queryValue = contentMatch;
   contentMatch = NULL;
   return queryValue;
}

char *find_getFieldValue(char *field, char *stringJson)
{
    char *valueString;
    cJSON *json;
    json=cJSON_Parse(stringJson);
    cJSON * value = cJSON_GetObjectItem(json, field);
    valueString = (value) ? value->valuestring : "";
    return valueString;
}

void find_readCollection(char *documentId, char* collection)
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char * path = pathCollectionDocument__(collection, NULL);
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Trying read, but Collection not exists!\n");//tracking error here.
        return;
    }

    while ((read = getline(&line, &len, fp)) != -1)
    {
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
        if(exists == 0)
        {
            arrayDocuments = appendStringArray(contentMatch, &indexArrayDocuments);
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
    char *dir = pathCollectionDocument__(documentName, NULL);
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
