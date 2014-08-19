/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Kaidun Huang
 * Student Number   : s3362938
 * Course Code      : COSC1076
 * Program Code     : BP232
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "gameboard.h"

/* Copies the master board to a local copy for each game */
void init_gameboard(enum cell_contents board[][BOARDWIDTH])
{
	
	int i, j;
	for( i=0; i<BOARDHEIGHT; i++) {
	  for( j=0; j<BOARDWIDTH; j++ ) {
		board[i][j] = master_board[i][j];
	  }
	}
	

    /* Delete this comment and write your own comments and code here*/
}

/* Prints the game board to the screen */
void display_gameboard(enum cell_contents board[][BOARDWIDTH])
{
	int i, j, k;
	
	//TODO: replace output later
	printf("     |");
	for( j=0; j<BOARDWIDTH; j++){
      printf("  %d  |", j);
	}
	printf("\n");
	for (k =0; k<8; k++) {
      printf("-------");  
	}
	printf("\n");
	
	
    for( i=0; i<BOARDHEIGHT; i++) {
	  printf("  %d  |", i);
	  for( j=0; j<BOARDWIDTH; j++ ) {
	
		if ( board[i][j] == RED ) {
		  printf("  %s  %s|", RED_DISPLAY, WHITE_RESET);
	    }
	    else if ( board[i][j] == K_RED ) {
		  printf("  %s  %s|", RED_KING_DISPLAY, WHITE_RESET);
		}
	    else if ( board[i][j] == WHITE ) {
		  printf("  %s  %s|", WHITE_DISPLAY, WHITE_RESET);
		}
		else if ( board[i][j] == K_WHITE ) {
		  printf("  %s  %s|", WHITE_KING_DISPLAY, WHITE_RESET);
		}
		else if ( board[i][j] == EMPTY ) {
		  printf("     %s|", WHITE_RESET);
		}
	  }
	  printf("\n");
	  
	  /* TODO: Replace the magic number */
	  for (k =0; k<8; k++) {
		printf("-------");  
	  }
	  printf("\n");
	}
	printf("%s", WHITE_RESET);
}
