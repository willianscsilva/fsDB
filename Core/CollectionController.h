/*
 * File:   WebSocketServer.h
 * Author: will
 *
 * Created on 16 de Julho de 2016, 13:38
 */
#include "../Default.h"

int checkCollectionExists(const char *collectionName);

int createCollection(const char *collectionName);

int checkDocumentExists(const char *collectionName);

int addDocumentInCollection(char* name, const char *documentValue);
