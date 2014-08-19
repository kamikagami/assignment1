/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Kaidun Huang
 * Student Number   : s3362938
 * Course Code      : COSC1076
 * Program Code     : BP232
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#ifndef GAME_H
#define GAME_H

#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "gameboard.h"
#include "scoreboard.h"

#define MOVE_LEN 8
#define INPUT_LEN 1
#define NAME_LEN 20

struct location
{
    unsigned x, y;
};

struct move
{
    struct location start;
    struct location end;
};

enum colour
{
    P_RED, P_WHITE
};

struct player
{
    char name[MAX_NAME_LEN+1];
    enum colour col;
};

enum move_type
{
    ATTACK, NORMAL, INVALID
};

enum str_result
{
    FAILURE, SUCCESS, RTM
};


typedef struct location Location;
typedef struct move Move;
typedef enum colour Colour;
typedef struct player Player;

/* Requirement 7 - Controls the flow of play in the game*/
void play_game(char * player_one, char * player_two, 
    struct result * outcome);

/* Requirement 6 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move curr_move, struct player * 
    current, enum cell_contents board[][BOARDWIDTH]);

/* Requirement  - Tests whether the next player has any valid moves */
BOOLEAN test_for_winner(struct player * next_player, 
    enum cell_contents board[][BOARDWIDTH]);

/* Requirement 5 - Handles the logic for the player's turn*/
enum str_result player_turn(struct player * current, 
    enum cell_contents board[][BOARDWIDTH]);


#endif
