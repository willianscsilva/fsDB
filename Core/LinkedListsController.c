#include "LinkedListsController.h"

linkedList_t *first = NULL; /* Pointer to the first list element */
linkedList_t *last = NULL; /* Pointer to the last list element */
linkedList_t *alloc; /* Pointer to make allocation */


int checkList_valueExists(char * value)
{
      struct linkedList_t *pointer;
      pointer = first;
      int returned = 0;
      printf("checkList_valueExists value before while: %s\n", value);
      while(pointer != NULL && strcmp(value, pointer->value) == 0)
      {
          printf("checkList_valueExists pointer->value after while: %s\n", pointer->value);
          returned = 1;
          pointer = pointer->next;
      }
      return returned;
}

void appendList_documments(char *value)
{
    alloc = ( struct linkedList_t * ) malloc( sizeof( struct linkedList_t ) );
    if ( !alloc )
    {
       printf( "Insufficient memory!\n" );
       exit(0);
    }
    printf("APPENDING: %s\n", value);
    alloc->value = value;
    printf("APPENDED: %s\n", value);
    if ( !first )
    {
            printf("FIRST\n");
            first = alloc;
            last = alloc;
    }
    else
    {
            printf("NOT FIRST\n");
            last->next = alloc;
            last = alloc;
    }
}

void freeing_AllocList()
{
    free(alloc);
}
