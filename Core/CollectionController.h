/*
 * File:   WebSocketServer.h
 * Author: will
 *
 * Created on 16 de Julho de 2016, 13:38
 */
void write__(char *path, char *value, const char * type);
char *pathCollection__(const char *collectionName);

int checkCollectionExists(const char *collectionName);

int createCollection(const char *collectionName);

int checkDocumentExists(char *pathCollection, char *documentName);

int addDocumentInCollection(char* collection, char *id, const char *documentValue);

char *find(char* collection, char *id, char *query);

void nullingLocalVars();

void find_readCollection(char *documentId, char* collection);

void find_documentsById(char * lineContent_collection, char *documentId);

void find_readList(char *query);

void find_execQueryInDocument(char *documentName, char *query);

void find_execQuery(char * line, char *query);

int checkQueryValueIsNumber(char * queryValue);

char *getFindOperator(char * queryValue);

char *getQueryField(char *query);

char *getQueryValue(char *query);

char *find_getFieldValue(char *field, char *stringJson);

int addInCollection__(char *path, char *value);

void addInDocument__(char *documentName, const char *value);

char *buildCollecionContent(char *documentName, char *documentId);
