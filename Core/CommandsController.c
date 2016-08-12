#include "CommandsController.h"

const char *commandList[] = {"checkCollectionExists","addDocumentInCollection"};

void initCommandsController(cJSON *json)
{
    parsingCommandObject(json);
}

void parsingCommandObject(cJSON *item)
{

    int i;
    for (i = 0 ; i < cJSON_GetArraySize(item) ; i++)
    {
        char *commandString, *valueString;
        cJSON * subitem = cJSON_GetArrayItem(item, i);
        cJSON * command = cJSON_GetObjectItem(subitem,"command");
        cJSON * value = cJSON_GetObjectItem(subitem,"value");
        commandString = (command) ? command->valuestring : 0;
        valueString = (value) ? value->valuestring : 0;

        if(value && value->type == cJSON_Object){
            char *outObj=0;
            outObj=cJSON_PrintUnformatted(value);
            valueString = outObj;
        }
        (command && value) ? parsingCommand(commandString, valueString):checkCommandAndValue_IsSetted(command, value, i);
    }
}

void parsingCommand(char *commandString, char *valueString)
{
    //printf("length of commandList: %d\n", COUNT(commandList));
    //printf("Command: %s\n", commandString);
    //printf("Value: %s\n", valueString);
    int i;
    for(i=0; i < COUNT(commandList); i++)
    {
        //printf("COMMANDS: %s\n", commandList[i]);
        int cmp = strcmp(commandString, commandList[i]);
        if(cmp == 0)
        {
            execInternalCommand(i, valueString);
        }
    }
}

void execInternalCommand(int commandCode, char *value)
{
    //printf("commandCode: %d - value: %s\n", commandCode, value);
    switch(commandCode)
    {
        case 0:
           //call fuction here
        break;
        case 1:
           //call fuction here
        break;
    }
}

void checkCommandAndValue_IsSetted(cJSON * command, cJSON * value, int pos)
{
    (!command) ? printf("Invalid Syntax: In Array position %i 'command' expression not found!\n", pos):1;
    (!value) ? printf("Invalid Syntax: In Array position %i 'value' expression not found!\n", pos):1;
}
