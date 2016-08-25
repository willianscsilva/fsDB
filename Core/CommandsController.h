#include "../Default.h"
#include "cJSON.h"
#define COUNT(x)  (int)(sizeof(x) / sizeof((x)[0]))
#define CREATE_COLLECTION 0
#define ADD_DOCUMENT_IN_COLLECTION 1

void initCommandsController();
void parsingCommandObject(cJSON *item);
void parsingCommand(char *commandString, char *collectionString, char *valueString, char *idString, int isObjt);
void checkAllFields_IsSetted(cJSON * command, cJSON * value, cJSON * collection, cJSON * id, int isObjt, int pos);
int execInternalCommand(int commandCode, char* collection, char *id, char *value, int isObjt);
