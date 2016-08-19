#include "CommandsController.h"
#include "CollectionController.h"

const char *commandList[] = {"createCollection","addDocumentInCollection"};

void initCommandsController(cJSON *json)
{
    parsingCommandObject(json);
}

void parsingCommandObject(cJSON *item)
{

    int i;
    for (i = 0 ; i < cJSON_GetArraySize(item) ; i++)
    {
        char *commandString, *valueString, *nameString;
        int isObjt = 0;
        cJSON * subitem = cJSON_GetArrayItem(item, i);
        cJSON * value = cJSON_GetObjectItem(subitem,"value");
        cJSON * command = cJSON_GetObjectItem(subitem,"command");
        cJSON * name = cJSON_GetObjectItem(subitem,"name");
        commandString = (command) ? command->valuestring : "";
        valueString = (value) ? value->valuestring : "";
        nameString = (name) ? name->valuestring : "";

        if(value && value->type == cJSON_Object)
        {
            isObjt = 1;
            char *outObj=0;
            outObj=cJSON_PrintUnformatted(value);
            valueString = outObj;
            (command && value && name) ? parsingCommand(commandString, nameString, valueString):checkAllFields_IsSetted(command, value, name, isObjt, i);
        }
        else
        {
            (command && value) ? parsingCommand(commandString, nameString, valueString):checkAllFields_IsSetted(command, value, name, isObjt, i);
        }
    }
}

void parsingCommand(char *commandString, char *nameString, char *valueString)
{
    int i;
    for(i=0; i < COUNT(commandList); i++)
    {
        int cmp = strcmp(commandString, commandList[i]);//comparing passing command with command in list.
        if(cmp == 0)
        {
            execInternalCommand(i, nameString, valueString);//if the command is found, say what, passing the code.
        }
    }
}

int execInternalCommand(int commandCode, char* name, char *value)
{
    //printf("commandCode: %d - value: %s\n", commandCode, value);
    int collectionCreated = 0;
    switch(commandCode)
    {
        case CREATE_COLLECTION:
           //printf("CREATE_COLLECTION - Command Code: %d and Value: %s\n", commandCode, value);
           collectionCreated = createCollection(value);
           (collectionCreated) ? printf("Collection created with successfully!\n") : printf("The collection already exists!\n");
           return 1;
        break;
        case ADD_DOCUMENT_IN_COLLECTION:
           //call fuction here
           //printf("ADD_DOCUMENT_IN_COLLECTION - Command Code: %d and Value: %s\n", commandCode, value);
           addDocumentInCollection(name, value);
           return 1;
        break;
    }
    return 0;
}

void checkAllFields_IsSetted(cJSON * command, cJSON * value, cJSON * name, int isObjt, int pos)
{
    (!command) ? printf("Invalid Syntax: In Array position %i 'command' field is not found!\n", pos):1;
    (!value) ? printf("Invalid Syntax: In Array position %i 'value' field is not found!\n", pos):1;
    if(isObjt)
    {
        (!name) ? printf("Invalid Syntax: In Array position %i 'name' field is not found!\n", pos):1;
    }
}
