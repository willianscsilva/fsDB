/* 
 * File:   SocketServer.h
 * Author: will
 *
 * Created on 23 de Maio de 2015, 00:15
 */
#include "../Default.h"
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

/*Create socket connection*/
void socketServer();

/*Sockets to processing*/
void doProcessing (int sock);