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
        //out=cJSON_Print(json);//print a formatted json with the line breaks etc.
        out=cJSON_PrintUnformatted(json);//print a json in a single line.
        cJSON_Delete(json);
        //printf("%s\n",out);
        free(out);
    }
}
