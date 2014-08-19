/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Kaidun Huang
 * Student Number   : s3362938
 * Course Code      : COSC1076
 * Program Code     : BP232
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "utility.h"

/* Tidy up residual data in stdin when encountering an error. You will 
 * need to use this when there is a possibility that there will be 
 * leftover characters in the input buffer. */
void read_rest_of_line(void)
{
    int ch;
    /* remove all characters from the buffer */
    while(ch = getc(stdin), ch!='\n' && ch!=EOF) 
        ;
    /* clear the error status of the input pointer */
    clearerr(stdin);
}

/* Get and return an integer provided by the user.
 *
 * Function courtesy of Steven Burrows (sdb@cs.rmit.edu.au)
 * Available on Blackboard as getInteger-basic.c 
 * and getString-basic.c
 */
int getInt(int* num, unsigned length, char* prompt, int min, int max)
{
    int finished = FALSE;
    char tempString[TEMP_STRING_LENGTH + 2];
    int tempInteger = 0;
    char* endPtr;

    /* Continue to interact with the user until the input is valid. */
    do
    {
        /* Provide a custom prompt. */
        printf("%s", prompt);

        /* Accept input. "+2" is for the \n and \0 characters. */
        fgets(tempString, length + 2, stdin);

        /* A string that doesn't have a newline character is too long. */
        if (tempString[strlen(tempString) - 1] != '\n')
        {
            printf("Input was too long.\n");
            read_rest_of_line();
        }
        else
        {
            /* Overwrite the \n character with \0. */
            tempString[strlen(tempString) - 1] = '\0';

            /* Convert string to an integer. */
            tempInteger = (int) strtol(tempString, &endPtr, BASE);

            /* Validate integer result. */
            if (strcmp(endPtr, "") != 0)
            {
                printf("Input was not numeric.\n");
            }
            else if (tempInteger < min || tempInteger > max)
            {
                printf("Input wasn't within range %d-%d.\n", min, max);
            }
            else
            {
                finished = TRUE;
            }
        }
    } while (finished == FALSE);

    /* Make the result integer available to calling function. */
    *num = tempInteger;

    return EXIT_SUCCESS;
}

#define CTRL_D (char)4

/* Get a string input from the user. */
int getString(char* string, unsigned length, char* prompt)
{
    int finished = FALSE;
    char tempString[TEMP_STRING_LENGTH + 2];
    char *res;

    /* Continue to interact with the user until the input is valid. */
    do
    {
        /* Provide a custom prompt. */
        printf("%s", prompt);

        /* Accept input. "+2" is for the \n and \0 characters. */
        res = fgets(tempString, length + 2, stdin);
        if( res == NULL ) {
		  /* if Ctrl+D is in the user input, then return a string "\D" */
		  string[0] = CTRL_D;
		  string[1] = '\0';
		  return;
		}

        /* A string that doesn't have a newline character is too long. */
        if (tempString[strlen(tempString) - 1] != '\n')
        {
            printf("Input was too long.\n");
            printf("%s\n", tempString);
            read_rest_of_line();
        }
        else
        {
            finished = TRUE;
        }

    } while (finished == FALSE);

    /* Overwrite the \n character with \0. */
    tempString[strlen(tempString) - 1] = '\0';

    /* Make the result string available to calling function. */
    strcpy(string, tempString);

    return EXIT_SUCCESS;
}
