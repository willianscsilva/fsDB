/* 
 * File:   Main.c
 * Author: will
 *
 * Created on 22 de Maio de 2015, 23:27
 */

#include "Default.h"
#include "Core/Core.h"

/*
 * 
 */
int main(int argc, char** argv) 
{  
    int validationReturn;
    validationReturn = argumentValidation(argc, argv);
    if(validationReturn == TRUE)
    {
        switchMode(argv);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    
    return (EXIT_SUCCESS);
}

