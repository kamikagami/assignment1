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
#include "game.h"
/* Req 2 -Initialises the scoreboard and sets all the strings to be 
 * empty*/
void init_scoreboard(struct result * scoreboard)
{
	memset(scoreboard, 0, sizeof(Result)*SCOREBOARDSIZE);
    /* Delete this comment and write your own comments and code here*/
}

/* Req 9 -Adds a result to the beginning of the scoreboard*/
void add_to_scoreboard(struct result * scoreboard, 
    struct result * latest_game)
{
    int index = 0;
 
    if(strlen(scoreboard[index].won) != 0)
    /* if there are already some results (aka players' name)in scoreboard,
     * find the last one. */
    {
		
		while(strlen(scoreboard[index].won) != 0)
		{
			/* reach the second last score */
			if(index == SCOREBOARDSIZE - 1)
			break;
			index++;
		}

		/* and move it to the last one */
		for(; index >0; --index)
		{
			strcpy(scoreboard[index].won, scoreboard[index-1].won);
			strcpy(scoreboard[index].lost, scoreboard[index-1].lost);
		}
	}

	strcpy(scoreboard[0].won, latest_game->won);
	strcpy(scoreboard[0].lost, latest_game->lost);	

}

/* Req 11 - Initialises the scoreboard and sets all the strings to be 
 * empty*/
void reset_scoreboard(struct result * scoreboard)
{
	memset(scoreboard, 0, sizeof(Result)*SCOREBOARDSIZE);
    /* Delete this comment and write your own comments and code here*/
}

/* Req 10 - Displays a formatted printout of the last 10 winners and 
 * losers*/
void display_scoreboard(struct result * scoreboard)
{
	int i = 0;
	char sbHeading[] =
	 {"APT English Draughts Tournament - History of Games Played.\n"};
	char winner[] = {"Winner"};
	char loser[] = {"Loser"};
	int nameLen = NAME_LEN+1;
	
	printf("%s\n", sbHeading);
	for(i = 0; i <= strlen(sbHeading); i++)
		printf("=");
	printf("\n|%-*s|%-*s\n", nameLen, winner, nameLen, loser);
	for(i = 0; i <= nameLen + nameLen; i++)
		printf("-");
	printf("\n");
	
	for(i = 0; i < SCOREBOARDSIZE; i++)
		printf("\n|%-*s|%-*s\n",nameLen, scoreboard[i].won, nameLen, scoreboard[i].lost);
	for(i = 0; i <= nameLen + nameLen; i++)
		printf("-");
	printf("\n");
	
    /* Delete this comment and write your own comments and code here*/
}

