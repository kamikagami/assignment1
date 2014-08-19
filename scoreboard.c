/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Kaidun Huang
 * Student Number   : s3362938
 * Course Code      : COSC1076
 * Program Code     : BP232
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/

#include "scoreboard.h"

/* Req 2 -Initialises the scoreboard and sets all the strings to be 
 * empty*/
void init_scoreboard(struct result * scoreboard)
{
	memset(scoreboard, 0, sizeof(Player)*SCOREBOARDSIZE);
    /* Delete this comment and write your own comments and code here*/
}

/* Req 9 -Adds a result to the beginning of the scoreboard*/
void add_to_scoreboard(struct result * scoreboard, 
    struct result * latest_game)
{
    /* Delete this comment and write your own comments and code here*/
}

/* Req 11 - Initialises the scoreboard and sets all the strings to be 
 * empty*/
void reset_scoreboard(struct result * scoreboard)
{
	memset(scoreboard, 0, sizeof(Player)*SCOREBOARDSIZE);
    /* Delete this comment and write your own comments and code here*/
}

/* Req 10 - Displays a formatted printout of the last 10 winners and 
 * losers*/
void display_scoreboard(struct result * scoreboard)
{
	int i = 0;
	char sbHeading[] = {"SCOREBOARD"};
	char winner[] = {"WINNER"};
	char loser[] = {"LOSER"};
	
	printf("%s\n", sbHeading);
	for(i = 0; i <= strlen(sbHeading); i++)
	printf("-");
	printf("\n");
	
    /* Delete this comment and write your own comments and code here*/
}

