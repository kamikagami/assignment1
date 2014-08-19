/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Kaidun Huang
 * Student Number   : s3362938
 * Course Code      : COSC1076
 * Program Code     : BP232
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#ifndef DRAUGHTS_H
#define DRAUGHTS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "gameboard.h"
#include "scoreboard.h"
#include "utility.h"

#define MENU_OPTIONS 4

enum
{
	PLAY_GAME = 1,
	DISPLAY_WINNERS,
	RESET_SCOREBOARD,
	EXIT
};
/* Delete this comment and create any type declarations or function 
 * prototypes that you might need here.*/
void printMenu(char **options, int size, char *menuMain);

#endif
