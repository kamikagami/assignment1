/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Kaidun Huang
 * Student Number   : s3362938
 * Course Code      : COSC1076
 * Program Code     : BP232
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
 
#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include "utility.h"
#include "game.h"
#define SCOREBOARDSIZE 10

struct result
{
    char won[MAX_NAME_LEN+1];
    char lost[MAX_NAME_LEN+1];
};

typedef struct result Result;

/* Req 2 -Initialises the scoreboard and sets all the strings to be 
 * empty*/
void init_scoreboard(struct result * scoreboard);

/* Adds a result to the beginning of the scoreboard*/
void add_to_scoreboard(struct result * scoreboard, 
    struct result * latest_game);

/* Req 11 - Initialises the scoreboard and sets all the strings to be 
 * empty*/
void reset_scoreboard(struct result * scoreboard);

/* Req 10 - Displays a formatted printout of the last 10 winners and 
 * losers*/
void display_scoreboard(struct result * scoreboard);

#endif
