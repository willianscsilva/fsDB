#!/bin/bash
rm -f fsDB
mkdir -p collections
gcc \
     Main.c \
     Core/Core.c \
     Core/SocketServer.c \
     Core/WebSocketServer.c \
     Core/cJSON.c \
     Core/JSONDataController.c \
     Core/CollectionController.c \
     Core/CommandsController.c \
     Core/Str2Md5.c \
     Core/RegexController.c \
     Core/ArrayController.c \
     Core/StringAuxiliary.c \
     -I/usr/local/include/nopoll \
     -L/usr/local/lib -lnopoll \
     -I/usr/include/openssl/ \
     -o fsDB \
     -lwebsockets \
     -lcrypto \
     -lpcre \
     -lm
