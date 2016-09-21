#include "ArrayController.h"

int checkStringValueExistsArray(char *value)
{
   if(indexOfStrings == 0)
   {
       return 0;
   }
   int i=0;
   while(i < indexOfStrings)
   {
       if(strcmp(value, arrayOfStrings[i]) == 0)
       {
           return 1;
       }
       i++;
   }
   return 0;
}

char **appendStringArray(char * value, int *externId)
{
    int len = strlen(value);
    *externId = indexOfStrings;
    if(arrayOfStrings)
    {
        arrayOfStrings = (char**)realloc(arrayOfStrings, indexOfStrings);
        arrayOfStrings[indexOfStrings] = malloc(len+1 * sizeof(char));
        strcpy(arrayOfStrings[indexOfStrings], value);
        indexOfStrings++;
    }
    else
    {
        arrayOfStrings = malloc(indexOfStrings);
        arrayOfStrings[indexOfStrings] = malloc(len+1 * sizeof(char));
        strcpy(arrayOfStrings[indexOfStrings], value);
        indexOfStrings++;
    }
    return arrayOfStrings;
}

void nullingStringArray()
{
    arrayOfStrings = NULL;
    indexOfStrings = 0;
}

char * getStringArrayValue(int index)
{
    if(index > indexOfStrings){
        printf("Index %d out of range!\n", index);
        return "";
    }
    return arrayOfStrings[index];
}
