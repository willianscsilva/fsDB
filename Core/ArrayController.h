#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char **arrayOfStrings;
int indexOfStrings;

int checkStringValueExistsArray(char *value);

char **appendStringArray(char * value, int *externId);

void nullingStringArray();

char * getStringArrayValue(int index);
