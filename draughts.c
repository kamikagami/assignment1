/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Kaidun Huang
 * Student Number   : s3362938
 * Course Code      : COSC1076
 * Program Code     : BP232
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "draughts.h"

int main (int argc, char *argv[])
{
    struct result scoreboard[SCOREBOARDSIZE];
    Player player1;
    Player player2;
    Result res;
    int input = 0;
    char replay[INPUT_LEN+1];
    char player1_name[NAME_LEN+1];
    char player2_name[NAME_LEN+1];
    char replayPrompt[] = {"Replay? (y for yes): "};
    char *name_prompt1 = {"Please input player 1's name: "};
    char *name_prompt2 = {"Please input player 2's name: "};
    char *menuHeader = {"\nEnglish Draughts - Main Menu"};
    char *menuOpt[MENU_OPTIONS] = {
		 "Play Game", "Display Winners", "Reset scoreboard", "Quit"};
	char *inputPrompt = {"Please select (1-4): "};
	enum cell_contents board[BOARDWIDTH][BOARDHEIGHT];
	BOOLEAN play = FALSE;
	
	init_scoreboard(scoreboard);
	
	while(input != EXIT)
	{
		printMenu(menuOpt, MENU_OPTIONS, menuHeader);
		getInt(&input, 1, inputPrompt, 1, MENU_OPTIONS);
		switch(input)
		{
			case PLAY_GAME:
				getString(player1_name, NAME_LEN, name_prompt1);
				getString(player2_name, NAME_LEN, name_prompt2);
			    do{
					play_game(player1_name, player2_name, &res);
					add_to_scoreboard(scoreboard, &res);
					getString(replay, INPUT_LEN+1, replayPrompt);
					if(*replay == 'y')
						play = TRUE;
					else 
						play = FALSE;
				}while(play == TRUE);
				break;
			case DISPLAY_WINNERS:
				printf("Display Winners\n");
				display_scoreboard(scoreboard);
				break;
			case RESET_SCOREBOARD:
				printf("\nReset Scoreboard Successfully.\n");
				reset_scoreboard(scoreboard);
				break;
			case EXIT:
				printf("Thanks for playing.\n");
				break;
			default:
				printf("Invalid option, please try again.\n");
				break;
		}
	}

    /* Delete this comment and write your own code here */
    
    return EXIT_SUCCESS;
}


void printMenu(char **menuOpt, int size, char *menuHeader)
{
	int i = 0;
	
	printf("%s\n", menuHeader);
	
	for (i = 0; i < size; i++)
	{
		printf("%d) %s\n", i + 1, menuOpt[i]);
	}
}
