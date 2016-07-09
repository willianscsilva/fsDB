/*
 * File:   WebSocketServer.h
 * Author: will
 *
 * Created on 7 de Junho de 2015, 21:16
 */
#include "../Default.h"
#include <nopoll.h>
#include "cJSON.h"

char * host;
char * port;
char *wsJson;

void listener_on_message (noPollCtx * ctx, noPollConn * conn, noPollMsg * msg, noPollPtr * user_data);

void initWebSocketServer();

void jsonParse();

int createCollection();

int addDocumentInCollection();

int checkCollectionExists();

int checkDocumentExists();
