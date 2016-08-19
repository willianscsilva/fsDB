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

int addDocumentInCollection(char* name, const char *documentValue);

int addInCollection__(char *path, char *value);

void addInDocument__(char *documentName, const char *value);
