#include "JSONDataController.h"
#include "CommandsController.h"

void jsonParse()
{
    char *out;cJSON *json;
    json=cJSON_Parse(wsJson);
    if (!json) {
        printf("jsonParseError before: [%s]\n",cJSON_GetErrorPtr());
    }
    else
    {
        initCommandsController(json);        
    }
}

char * buildReturnToClientSide(char **arrayReturn, int indexArray)
{
    cJSON *rootArray, *rootObj, *db, *dbArray, *rootArrayReturn;
    char *out;
    register int i;
    rootArray=cJSON_CreateArray();
    cJSON_AddItemToArray(rootArray, db = cJSON_CreateObject());
    cJSON_AddItemToObject(db, "dbObject", dbArray = cJSON_CreateArray());
    for(i=0; i<=indexArray; i++)
    {
        cJSON_AddItemToArray(dbArray, rootObj = cJSON_CreateObject());
        cJSON_AddStringToObject(rootObj, "successReturn", arrayReturn[i]);
        cJSON_AddStringToObject(rootObj, "failureReturn", "NULL");
    }
    return cJSON_PrintUnformatted(rootArray);
}
