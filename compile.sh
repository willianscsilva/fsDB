#!/bin/bash
rm -f fsDB
gcc \
     Main.c \
     Core/Core.c \
     Core/SocketServer.c \
     Core/WebSocketServer.c \
     Core/cJSON.c \
     -I/usr/local/include/nopoll \
     -L/usr/local/lib -lnopoll \
     -o fsDB \
     -lwebsockets \
     -lm
