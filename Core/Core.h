/* 
 * File:   Core.h
 * Author: will
 *
 * Created on 22 de Maio de 2015, 23:29
 */
#include "../Default.h"
#include "SocketServer.h"
#include "WebSocketServer.h"

#define WS "ws"
#define SKT "skt"
#define TRUE 1
#define FALSE 0
#define TOTAL_PARAMETERS 3

int argumentValidation(int argc, char** argv);
void switchMode(char** params);