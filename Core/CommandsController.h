#include "../Default.h"
#include "cJSON.h"
#define COUNT(x)  (int)(sizeof(x) / sizeof((x)[0]))

void initCommandsController();
void parsingCommandObject(cJSON *item);
void parsingCommand(char *commandString, char *valueString);
void checkCommandAndValue_IsSetted(cJSON * command, cJSON * value, int pos);
void execInternalCommand(int commandCode, char *value);
