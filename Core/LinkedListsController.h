#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct linkedList_t
{
   char *value;
   struct linkedList_t *next;
}linkedList_t;

int checkList_valueExists(char * value);

void appendList_documments(char *value);

void freeing_AllocList();
