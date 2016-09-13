#include "CommandsController.h"
#include "CollectionController.h"

const char *commandList[] = {"createCollection","addDocument", "find"};

void initCommandsController(cJSON *json)
{
    parsingCommandObject(json);
}

void parsingCommandObject(cJSON *item)
{

    int i;
    for (i = 0 ; i < cJSON_GetArraySize(item) ; i++)
    {
        char *commandString, *valueString, *collectionString, *idString;
        int isObjt = 0;
        cJSON * subitem = cJSON_GetArrayItem(item, i);
        cJSON * value = cJSON_GetObjectItem(subitem,"value");
        cJSON * command = cJSON_GetObjectItem(subitem,"command");
        cJSON * collection = cJSON_GetObjectItem(subitem,"collection");
        cJSON * id = cJSON_GetObjectItem(subitem,"id");
        commandString    = (command) ? command->valuestring : "";
        valueString      = (value) ? value->valuestring : "";
        collectionString = (collection) ? collection->valuestring : "";
        idString         = (id) ? id->valuestring : "";

        if(value && value->type == cJSON_Object)
        {
            isObjt = 1;
            char *outObj=0;
            outObj=cJSON_PrintUnformatted(value);
            valueString = outObj;
            (command && value && collection && idString) ? parsingCommand(commandString, collectionString, idString, valueString, isObjt):checkAllFields_IsSetted(command, value, collection, id, isObjt, i);
        }
        else
        {
            (command && value) ? parsingCommand(commandString, collectionString, idString, valueString, isObjt):checkAllFields_IsSetted(command, value, collection, id, isObjt, i);
        }
    }
}

void parsingCommand(char *commandString, char *collectionString, char *idString, char *valueString, int isObjt)
{
    int i;
    for(i=0; i < COUNT(commandList); i++)
    {
        int cmp = strcmp(commandString, commandList[i]);//comparing passing command with command in list.
        if(cmp == 0)
        {
            execInternalCommand(i, collectionString, idString, valueString, isObjt);//if the command is found, say what, passing the code.
        }
    }
}

int execInternalCommand(int commandCode, char* collection, char *id, char *value, int isObjt)
{
    //printf("commandCode: %d - value: %s\n", commandCode, value);
    int collectionCreated = 0;
    int addDocument = 0;
    switch(commandCode)
    {
        case CREATE_COLLECTION:
           collectionCreated = createCollection(value);
           (collectionCreated) ? printf("Collection created with successfully!\n") : printf("The collection already exists!\n");
           return 1;
        break;
        case ADD_DOCUMENT_IN_COLLECTION:
           if(isObjt == 1)
           {
               addDocument = addDocumentInCollection(collection, id, value);
               (addDocument) ? printf("Add Document with successfully!\n") : 0;
               return 1;
           }
           else
           {
               printf("the 'value' field does not contain a json object!\n");
               return 0;
           }
        break;
        case FIND:
            if(isObjt == 1)
            {
                find(collection, id, value);                
                return 1;
            }
            else
            {
                printf("the 'value' field does not contain a json object!\n");
                return 0;
            }
        break;
    }
    return 0;
}

void checkAllFields_IsSetted(cJSON * command, cJSON * value, cJSON * collection, cJSON * id, int isObjt, int pos)
{
    (!command) ? printf("Invalid Syntax: In Array position %i 'command' field is not found!\n", pos):1;
    (!value) ? printf("Invalid Syntax: In Array position %i 'value' field is not found!\n", pos):1;
    if(isObjt)
    {
        (!collection) ? printf("Invalid Syntax: In Array position %i 'collection' field is not found!\n", pos):1;
        (!id) ? printf("Invalid Syntax: In Array position %i 'id' field is not found!\n", pos):1;
    }
}
