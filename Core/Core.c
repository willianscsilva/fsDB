#include "Core.h"

int argumentValidation(int argc, char** argv)
{
    //subtract 1 because the first argument is the name of the executable
    int parameters_received = argc-1;
    if(parameters_received != TOTAL_PARAMETERS)
    {
        printf("Usage %s [skt or ws] hostname port\n", argv[0]);
        return FALSE;
    }
    //first argument needed "skt" or "ws"
    if(strcmp(argv[1], SKT) != 0 && strcmp(argv[1], WS) != 0)
    {
        printf("Passing argument 1 '%s' but was expected 'ws' or 'skt'\n", argv[1]);
        return FALSE;
    }
    return TRUE;
}

void switchMode(char** params)
{

    if(strcmp(params[1], WS) == 0)
    {
        initWebSocketServer(params);
    }
    else if(strcmp(params[1], SKT) == 0)
    {
        socketServer(params);
    }
}
