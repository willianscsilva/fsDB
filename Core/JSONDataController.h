/*
 * File:   WebSocketServer.h
 * Author: will
 *
 * Created on 16 de Julho de 2016, 13:25
 */
#include "../Default.h"
#include "cJSON.h"

char *wsJson;

void jsonParse();

char * buildReturnToClientSide(char **arrayReturn, int indexArray);
