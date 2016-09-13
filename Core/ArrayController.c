#include "ArrayController.h"

void appendStringArray(char * value)
{
    int len = strlen(value);

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
}

char * getStringArrayValue(int index)
{
    if(index > indexOfStrings){
        printf("Index %d out of range!\n", index);
        return "";
    }
    return arrayOfStrings[index];
}

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
