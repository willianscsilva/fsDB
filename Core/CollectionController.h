/*
 * File:   WebSocketServer.h
 * Author: will
 *
 * Created on 16 de Julho de 2016, 13:38
 */
#include "../Default.h"

int createCollection(const char *collectionName);

int addDocumentInCollection(const char *collectionName);

int checkCollectionExists(const char *collectionName);

int checkDocumentExists(const char *collectionName);
