/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2014 Assignment #1 
 * Full Name        : Kaidun Huang
 * Student Number   : s3362938
 * Course Code      : COSC1076
 * Program Code     : BP232
 * Start up code provided by Paul Miller and Virginia King
 **********************************************************************/
#include "game.h"

#define POS_LEN 50
#define CTRL_D 4

Colour get_colour() {
  static int res = NULL;
  if ( res == P_RED ) {
	res = P_WHITE;
	return res;  
  }
  else if ( res == P_WHITE ) {
	res = P_RED;
	return res;
  }
  else{
    /* if it's first time then generate colour randmonly */
    srand(time(NULL));
    res = (int)(rand() % 10 + 1);
    if (res >= 5 ) {
   	  res = P_RED;
   	  return res;
    }
    else {
	  res = P_WHITE;
	  return res;
    }
 }
}


/* Requirement 7 - Controls the flow of play in the game*/
void play_game(char * player_one, char * player_two, 
    struct result * outcome)
{
    enum cell_contents board[BOARDWIDTH][BOARDHEIGHT];
    Player p1, p2;
    enum str_result res;

    
    /* init players */
    strcpy(p1.name, player_one);
    strcpy(p2.name, player_two);
    p1.col = get_colour();
    p2.col = get_colour();
    
   
    while(TRUE) {
      init_gameboard(board);
      display_gameboard(board);
      
      /* the first time */
      while(TRUE) {
        if (p1.col  == P_RED ) {
	      res = player_turn(&p1, &board);
	    }
	    else {
		  res = player_turn(&p2, &board);
	    }
	    
	    if ( res == SUCCESS )
	      break; 
	    else if ( res == RTM ) 
	      return; /* end the game */
	  }
	  
      break;
    }
    
  

}

/* token position */
BOOLEAN get_pos(char *loc, Move *m) {
	 
    int i,j,k,l;
    char *tok = NULL;
    char ori_str[STRING_INPUT_LENGTH+1];
    char dst_str[STRING_INPUT_LENGTH+1];
    char *current_player;
    char *dash = {"-"};
    char *comma = {","}; 
     
    /* sample move string:  1,2-3,4 */
    tok = strtok(loc, dash);
    if (!tok) { 
	  /* '-' is not existed */
	  
	  return FALSE;
	}
	
    strcpy(ori_str, tok);
    tok = strtok(NULL, dash);
    if (!tok) {
	  /* user does not input dest */
      return FALSE;
	}
	strcpy(dst_str, tok);
	tok = strtok(NULL, dash);
	if(tok) {
	  /* the silly user input things like 1,2-3,4-5,6 */
	  return FALSE;
	}


    /*ori*/
	tok = NULL;
	tok = strtok(ori_str, comma);
	if (!tok){
	 /* ',' not existed */
	 return FALSE;
	}
	/* TODO: err handling here */
	(m->start).x = atoi(tok);
	tok = strtok(NULL, comma);
	(m->start).y = atoi(tok); 

	
	/*dst*/
    tok = NULL;
	tok = strtok(dst_str, comma);
	if (!tok){
	 /* ',' not existed */
	 return FALSE;
	}
	(m->end).x = atoi(tok);
	tok = strtok(NULL, comma);
	(m->end).y = atoi(tok); 
 
    return TRUE;
}


/* display gameboard after every valid move */
void update_board(Move m, Colour col, enum cell_contents board[][BOARDWIDTH]) {
  
  /* set dst */
  if ( col == P_RED ) 
   board[m.end.x][m.end.y] = RED;
  else
   board[m.end.x][m.end.y] = WHITE;
   
  /* clear ori */
  board[m.start.x][m.start.y] = EMPTY;
  
  display_gameboard(board);
   
}

/* Requirement 5 - Handles the logic for the player's turn*/
enum str_result player_turn(struct player * current, 
    enum cell_contents board[][BOARDWIDTH])
{
   enum move_type mt;
   Move m;
   int res;
   char pos_str[POS_LEN];
   char turn_prompt[PROMPT_LENGTH];
   char prompt[] =  {"%sIt is %s's turn. Please enter a move [press\
enter or ctrl-D to quite the current game]: "};
    
   if ( current->col == P_RED ) 
     sprintf(turn_prompt, prompt, "[Red Colour]" ,current->name);
   else
     sprintf(turn_prompt, prompt, "[White Colour]" ,current->name);
   
   while(TRUE) {
     getString(pos_str, POS_LEN, turn_prompt);
     if ( strchr(pos_str, CTRL_D) != NULL ){ /* user input Ctrl + D */
       return RTM;
	 }
	 res = get_pos(pos_str, &m);
	 mt = is_valid_move(m, current, board);
	 if (!res || mt == INVALID) {
	   printf("Pleaes input the valid moves\n"); 
	   continue;
	 }
	 break;
   }
   
   update_board(m, current->col, board);

}

/* Requirement 6 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move next_move, 
    struct player * current, enum cell_contents board[][BOARDWIDTH])
{ 
	Location sample_dst1, sample_dst2;
	
    /* if ori valid */
    if ( next_move.start.x > BOARDWIDTH || next_move.start.x < 0 )
      return INVALID;
    if ( next_move.start.y > BOARDHEIGHT || next_move.start.y < 0 )
      return INVALID;
    
    if ( current->col == P_RED && board[next_move.start.x][next_move.start.y] == RED ) {}
    else if ( current->col == P_WHITE && board[next_move.start.x][next_move.start.y] == WHITE ) {}
    else if ( current->col == P_RED && board[next_move.start.x][next_move.start.y] == K_RED ) {}
    else if ( current->col == P_WHITE && board[next_move.start.x][next_move.start.y] == K_WHITE ) {}
    else if (board[next_move.start.x][next_move.start.y] == EMPTY) return INVALID;
    else return INVALID;
    
    /* if dst valid */
    if ( board[next_move.end.x][next_move.end.y] != EMPTY ) {
	  return INVALID;
	}
    if ( next_move.end.x > BOARDWIDTH || next_move.end.x < 0 )
      return INVALID;
    if ( next_move.end.y > BOARDHEIGHT || next_move.end.y < 0 )
      return INVALID;
    
    sample_dst1.x = next_move.start.x + 1;
    sample_dst1.y = next_move.start.y - 1;
    
    sample_dst2.x = next_move.start.x + 1;
    sample_dst1.y = next_move.start.y + 1;
    
    if ( next_move.end.x == sample_dst1.x && 
         next_move.end.y == sample_dst1.y ){}
    else if ( next_move.end.x == sample_dst2.x &&
              next_move.end.y == sample_dst2.y ) {}
    else
      return INVALID;          
    
    /* TODO attack and King */
    
    
    return NORMAL;
}

/* Requirement  - Tests whether the next player has any valid moves */
BOOLEAN test_for_winner(struct player * next_player, 
    enum cell_contents board[][BOARDWIDTH])
{
    BOOLEAN has_moves = TRUE;

    return has_moves;
}
