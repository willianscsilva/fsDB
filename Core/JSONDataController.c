
#include "JSONDataController.h"

int jsonParse()
{
    char *out;cJSON *json;
    json=cJSON_Parse(wsJson);
    if (!json) {
        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
        return 0;
    }
    else
    {
        out=cJSON_Print(json);
        cJSON_Delete(json);
        //printf("%s\n",out);
        free(out);
        return 1;
    }
}
