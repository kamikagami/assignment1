/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Kaidun Huang
 * Student Number   : s3362938
 * Course Code      : COSC1076
 * Program Code     : BP232
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 20


/*used for getInt() */
#define INT_INPUT_LENGTH 11
#define PROMPT_LENGTH 200
#define TEMP_STRING_LENGTH 20
#define BASE 10

/*used for getString()*/
#define STRING_INPUT_LENGTH 20
#define CTRL_D (char) 4

void read_rest_of_line(void);
int getInt(int* in, unsigned len, char* prompt, int min, int max);
int getString(char* str, unsigned len, char* prompt);

typedef enum
{
    FALSE, TRUE
} BOOLEAN;

/*Clears residual data from stdin*/
void read_rest_of_line(void);

#endif
