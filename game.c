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

#define POS_LEN 10
#define P1 0
#define P2 1

/* assign colour */
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
    int current;
    enum str_result res;


    /* init players */
    strcpy(p1.name, player_one);
    strcpy(p2.name, player_two);
    p1.col = get_colour();
    p2.col = get_colour();


    while(!FALSE) {
        init_gameboard(board);
        display_gameboard(board);

        /* the first time */
        while(TRUE) {
            if (p1.col  == P_RED ) {
                current = P1;
                res = player_turn(&p1, &board);
            }
            else {
                current = P2;
                res = player_turn(&p2, &board);
            }

            if ( res == SUCCESS )
                break; 
            else if ( res == RTM ) 
                return; /* end the game */
        }

        while(TRUE) {
            if ( current == P1 ) {
                /* if current player is p1 then it's p2's turn */
                res = player_turn(&p2, &board);
                current = P2;
            }  
            else {
                /* if current player is p2 then it's p1's turn */
                res = player_turn(&p1, &board);
                current  = P1;	
            }

            if ( res == RTM )
                return; /* end the game */
            else if ( res == FAILURE ) {
                /* rollback */
                if ( current == P2 ) {
                    current = P1;
                    continue;
                }
                else {
                    current = P2;
                    continue;
                }
            }

            if ( current == P1 ) {
                if ( !test_for_winner(&p2, &board) )  
                    break;
            }
            else {
                if ( !test_for_winner(&p1, &board) )  
                    break;
            }


        }

        if ( current == P2 ) {
            /* p2 won */
            printf("Player %s won, Play %s lost\n", p2.name, p1.name);
            strcpy(outcome->won, p2.name);
            strcpy(outcome->lost, p1.name);
        }
        else {
            /* p1 won */
            printf("Player %s won, Play %s lost\n", p1.name, p2.name);
            strcpy(outcome->won, p1.name);
            strcpy(outcome->lost, p2.name);
        }

        break;
    }

}

/* token position */
BOOLEAN get_pos(char *loc, Move *m) {

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

    int mid_x, mid_y;

    /* set dst */
    if ( col == P_RED ) { 
        if(m.end.x == BOARDHEIGHT -1 ) {
            /* become king */
            board[m.end.x][m.end.y] = K_RED;
        }
        else {
            if( board[m.start.x][m.start.y] == RED ) {
              board[m.end.x][m.end.y] = RED;
            }
            else {
              board[m.end.x][m.end.y] = K_RED;
	    }
        }
    }
    else {
        if(m.end.x == MIN_WIDTH ) {
            /* become king */	
            board[m.end.x][m.end.y] = K_WHITE;
        }
        else {

            if( board[m.start.x][m.start.y] == WHITE ) {
              board[m.end.x][m.end.y] = WHITE;
            }
            else {
              board[m.end.x][m.end.y] = K_WHITE;
	    }
        }
    } 

    /* clear ori */
    board[m.start.x][m.start.y] = EMPTY;

    if ( abs(m.end.x - m.start.x) == 2 &&
            abs(m.end.y - m.start.y) == 2 ) {
        /* It's an attack */
        mid_x = (int)m.start.x + ((int)m.end.x - (int)m.start.x)/2;
        mid_y = (int)m.start.y + ((int)m.end.y - (int)m.start.y)/2;
        board[mid_x][mid_y] = EMPTY; 	   
    }

    display_gameboard(board);

}


BOOLEAN continue_attack() {

    char pos_str[POS_LEN];
    char attack_again[] = { "You attacked! Would you like to attempt a further attack move\
        with this token? [y for yes, n for no or press enter or ctrl-D\
            to quit the current game]:" };

    while(TRUE) {
        getString(pos_str, POS_LEN, attack_again); 
        if ( strcmp(pos_str, "y") == 0 ||
                strcmp(pos_str, "n") == 0 ) {
            printf("Please input 'y' or 'n'\n");
            break;	  
        }
    }
    if ( strcmp(pos_str, "n") == 0 )
        return FALSE; 
    else 
        return TRUE;
}

/* Requirement 5 - Handles the logic for the player's turn*/
enum str_result player_turn(struct player * current, 
        enum cell_contents board[][BOARDWIDTH])
{
    enum move_type mt;
    Move m, attampt_m;
    int res;
    char pos_str[POS_LEN];
    char turn_prompt[PROMPT_LENGTH];
    char prompt[] =  {"%sIt is %s's turn.\
        Please enter a move(e.g. 2,0-3,1) [press enter or ctrl-D to\
            quit the current game]: "};


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
            printf("Pleaes input again.\n"); 
            return FAILURE;
        }

        update_board(m, current->col, board);

        if ( mt == ATTACK ) {
            attampt_m.start.x = m.end.x;
            attampt_m.start.y = m.end.y;

            /* Case 1 */
            attampt_m.end.x = attampt_m.start.x + 2;
            attampt_m.end.y = attampt_m.start.y - 2;
            if( m.start.x + 2 < BOARDHEIGHT && m.start.y - 2 >= MIN_WIDTH ) { 
                printf("case 1: %d,%d\n", attampt_m.end.x, attampt_m.end.y);
                if ( is_valid_move(attampt_m, current, board) == ATTACK ) {		 
                    if ( continue_attack() ) 
                        continue;
                    else
                        break;
                }	
            }

            /* Case 2 */
               
	    attampt_m.end.x = attampt_m.start.x + 2;
	    attampt_m.end.y = attampt_m.start.y + 2;
            if( m.start.x + 2 < BOARDHEIGHT && m.start.y + 2 < BOARDWIDTH ) {
                printf("case 2: %d,%d\n", attampt_m.end.x, attampt_m.end.y);
                if ( is_valid_move(attampt_m, current, board) == ATTACK ) {
                    if ( continue_attack() ) 
                        continue;
                    else
                        break; 

                }
            }		

            /* Case 3 */
            attampt_m.end.x = attampt_m.start.x - 2;
            attampt_m.end.y = attampt_m.start.y - 2;
            if( m.start.x - 2 >= MIN_WIDTH && m.start.y - 2 >= MIN_WIDTH ) {
                printf("case 3: %d,%d\n", attampt_m.end.x, attampt_m.end.y); 
                if ( is_valid_move(attampt_m, current, board) == ATTACK ) {  
                    if ( continue_attack() ) 
                        continue;
                    else
                        break;  	   
                }
            }

            /* Case 4 */
            attampt_m.end.x = attampt_m.start.x - 2;
            attampt_m.end.y = attampt_m.start.y + 2;
            if( m.start.x - 2 >= MIN_WIDTH && m.start.y + 2 < BOARDWIDTH ) { 
		printf("case 4: %d,%d\n", attampt_m.end.x, attampt_m.end.y);
                if ( is_valid_move(attampt_m, current, board) == ATTACK ) {  
                    if ( continue_attack() ) 
                        continue;
                    else
                        break;  	   
                }  
            }
        } 

        break;  
    } /* while */
    return SUCCESS;
}

/* Requirement 6 - Tests to see whether a move is valid or not*/
enum move_type is_valid_move(struct move next_move, 
        struct player * current, enum cell_contents board[][BOARDWIDTH])
{ 
    Location sample_dst1, sample_dst2, sample_dst3, sample_dst4, 
             attack_sample_dst1, attack_sample_dst2, attack_sample_dst3, 
             attack_sample_dst4;

    /* General validation */

    /* if ori valid */
    if ( next_move.start.x >= BOARDWIDTH || next_move.start.x < MIN_WIDTH ) {
        printf("Please input the move less than the maximum range ");
        return INVALID;
    }

    if ( next_move.start.y >= BOARDHEIGHT || next_move.start.y < MIN_WIDTH ) {
        printf("Please input the move less than the maximum range ");
        return INVALID;
    }

    if ( current->col == P_RED && board[next_move.start.x][next_move.start.y] == RED ) {}
    else if ( current->col == P_WHITE && board[next_move.start.x][next_move.start.y] == WHITE ) {}
    else if ( current->col == P_RED && board[next_move.start.x][next_move.start.y] == K_RED ) {}
    else if ( current->col == P_WHITE && board[next_move.start.x][next_move.start.y] == K_WHITE ) {}
    else if (board[next_move.start.x][next_move.start.y] == EMPTY) {
        printf("There is no token here\n");
        return INVALID;
    }
    else {
        printf("Please move your own token\n");
        return INVALID;
    }


    /* if dst valid */
    if ( next_move.end.x >= BOARDWIDTH || next_move.end.x < MIN_WIDTH ) {
        printf("Please input the move less than the maximum range.\n");
        return INVALID;
    }
    if ( next_move.end.y >= BOARDHEIGHT || next_move.end.y < MIN_WIDTH ) {
        printf("Please input the move less than the maximum range.\n");
        return INVALID;
    }

    if ( board[next_move.end.x][next_move.end.y] != EMPTY ) {
        printf("There is token at your destination\n");
        return INVALID;
    }




    /* Player Validation  */

    if ( current->col == P_RED && ( board[next_move.start.x][next_move.start.y] == RED || board[next_move.start.x][next_move.start.y] == K_RED) ) {
        /* Calculate the sample dsts */
        sample_dst1.x = next_move.start.x + 1;
        sample_dst1.y = next_move.start.y - 1;
        sample_dst2.x = next_move.start.x + 1;
        sample_dst2.y = next_move.start.y + 1;

        attack_sample_dst1.x = next_move.start.x + 2;
        attack_sample_dst1.y = next_move.start.y - 2;
        attack_sample_dst2.x = next_move.start.x + 2;
        attack_sample_dst2.y = next_move.start.y + 2;
    }
    else if (current->col == P_WHITE && ( board[next_move.start.x][next_move.start.y] == WHITE || board[next_move.start.x][next_move.start.y] == K_WHITE)) {
        /* Calculate the sample dsts */
        sample_dst1.x = next_move.start.x - 1 ;
        sample_dst1.y = next_move.start.y - 1;  
        sample_dst2.x = next_move.start.x - 1;
        sample_dst2.y = next_move.start.y + 1;

        attack_sample_dst1.x = next_move.start.x - 2;
        attack_sample_dst1.y = next_move.start.y - 2;
        attack_sample_dst2.x = next_move.start.x - 2;
        attack_sample_dst2.y = next_move.start.y + 2;
    }


    if ( current->col == P_RED && board[next_move.start.x][next_move.start.y] == K_RED ) {
        /* Calculate the sample dsts */
        sample_dst3.x = next_move.start.x - 1 ;
        sample_dst3.y = next_move.start.y - 1;   
        sample_dst4.x = next_move.start.x - 1;
        sample_dst4.y = next_move.start.y + 1;

        attack_sample_dst3.x = next_move.start.x - 2;
        attack_sample_dst3.y = next_move.start.y - 2;
        attack_sample_dst4.x = next_move.start.x - 2;
        attack_sample_dst4.y = next_move.start.y + 2;
    }
    else if ( current->col == P_WHITE && board[next_move.start.x][next_move.start.y] == K_WHITE ) {
        /* Calculate the sample dsts */
        sample_dst3.x = next_move.start.x + 1 ;
        sample_dst3.y = next_move.start.y - 1;    
        sample_dst4.x = next_move.start.x + 1;
        sample_dst4.y = next_move.start.y + 1;

        attack_sample_dst3.x = next_move.start.x + 2;
        attack_sample_dst3.y = next_move.start.y - 2;
        attack_sample_dst4.x = next_move.start.x + 2;
        attack_sample_dst4.y = next_move.start.y + 2;
    }


    /* The following is the validation for attack move */
    if (abs(next_move.start.x - next_move.end.x) == 2 && abs(next_move.start.y - next_move.end.y) == 2 ) { 
        /* The move is an attack move */

        if ( next_move.end.x == attack_sample_dst1.x && next_move.end.y == attack_sample_dst1.y ) {
            if ( board[attack_sample_dst1.x][attack_sample_dst1.y] != EMPTY ) {
                printf("There is token at your destination\n");
                return INVALID;
            }

            /* sample 1 */
            if ((( board[next_move.start.x][next_move.start.y] == RED || board[next_move.start.x][next_move.start.y] == K_RED )
                        &&  (board[sample_dst1.x][sample_dst1.y] == WHITE ||board[sample_dst1.x][sample_dst1.y] == K_WHITE)) ||
                    ( (board[next_move.start.x][next_move.start.y] == WHITE || board[next_move.start.x][next_move.start.y] == K_WHITE  ) 
                      && (board[sample_dst1.x][sample_dst1.y] == RED || board[sample_dst1.x][sample_dst1.y] == K_RED )) ){
                return ATTACK;
            }
            else {
                printf("You can't attack your own token!\n");
                return INVALID;
            }


        }
        else if ( next_move.end.x == attack_sample_dst2.x && next_move.end.y == attack_sample_dst2.y ) {
            if ( board[attack_sample_dst2.x][attack_sample_dst2.y] != EMPTY ) {
                printf("There is token at your destination\n");
                return INVALID;
            }  

            /* sample 2 */
            if ( next_move.end.x == attack_sample_dst2.x && next_move.end.y == attack_sample_dst2.y ) {

                if ( (( board[next_move.start.x][next_move.start.y] == RED || board[next_move.start.x][next_move.start.y] == K_RED )
                            &&  (board[sample_dst2.x][sample_dst2.y] == WHITE ||board[sample_dst2.x][sample_dst2.y] == K_WHITE)) ||
                        ( (board[next_move.start.x][next_move.start.y] == WHITE || board[next_move.start.x][next_move.start.y] == K_WHITE  ) 
                          && (board[sample_dst2.x][sample_dst2.y] == RED || board[sample_dst2.x][sample_dst2.y] == K_RED )) ){
                    return ATTACK;
                }
                else {
                    printf("You can't attack your own token!\n");
                    return INVALID;
                } 
            }
        }
        else if ( board[next_move.start.x][next_move.start.y] == RED ||
                board[next_move.start.x][next_move.start.y] == WHITE ) { 		  
            /* token is either red or white but not matach any sample destinations, it's a invalid move */
            printf("Please follow the rule to do the moving\n");
            return INVALID;          
        }
        else {
            /* The token is king, keep validation */
            if ( next_move.end.x == attack_sample_dst3.x && next_move.end.y == attack_sample_dst3.y ){
                /* sample 3 */
                if ( board[attack_sample_dst3.x][attack_sample_dst3.y] != EMPTY ) {
                    printf("There is token at your destination\n");
                    return INVALID;
                }   

                if ( (( board[next_move.start.x][next_move.start.y] == RED || board[next_move.start.x][next_move.start.y] == K_RED )
                            &&  (board[sample_dst3.x][sample_dst3.y] == WHITE ||board[sample_dst3.x][sample_dst3.y] == K_WHITE)) ||
                        ( (board[next_move.start.x][next_move.start.y] == WHITE || board[next_move.start.x][next_move.start.y] == K_WHITE  ) 
                          && (board[sample_dst3.x][sample_dst3.y] == RED || board[sample_dst3.x][sample_dst3.y] == K_RED )) ){
                    return ATTACK;
                }
                else {
                    printf("You can't attack your own token!\n");
                    return INVALID;
                }
            }
            else if ( next_move.end.x == attack_sample_dst4.x && next_move.end.y == attack_sample_dst4.y ) {
                /* sample 4 */
                if ( board[attack_sample_dst4.x][attack_sample_dst4.y] != EMPTY ) {
                    printf("There is token at your destination\n");
                    return INVALID;
                }   

                if ( (( board[next_move.start.x][next_move.start.y] == RED || board[next_move.start.x][next_move.start.y] == K_RED )
                            &&  (board[sample_dst4.x][sample_dst4.y] == WHITE ||board[sample_dst4.x][sample_dst4.y] == K_WHITE)) ||
                        ( (board[next_move.start.x][next_move.start.y] == WHITE || board[next_move.start.x][next_move.start.y] == K_WHITE  ) 
                          && (board[sample_dst4.x][sample_dst4.y] == RED || board[sample_dst4.x][sample_dst4.y] == K_RED )) ){
                    return ATTACK;
                }
                else {
                    printf("You can't attack your own token!\n");
                    return INVALID;
                }

            }
            else {
                /* token is either red_king or white_king but not matach any sample destinations, it's a invalid move */
                printf("Please follow the rule to do the moving\n");
                return INVALID;          
            }
        }


    }


    /* The following is the validation for non-attack move */

    if ( next_move.end.x == sample_dst1.x && next_move.end.y == sample_dst1.y ){ return NORMAL; }
    else if ( next_move.end.x == sample_dst2.x && next_move.end.y == sample_dst2.y ) { return NORMAL; }
    else if ( board[next_move.start.x][next_move.start.y] == RED ||
            board[next_move.start.x][next_move.start.y] == WHITE ) { 		  
        /* token is either red or white but not matach any sample destinations, it's a invalid move */
        printf("Please follow the rule to do the moving\n");
        return INVALID;          
    }
    else {
        /* The token is king, keep validation */
        if ( next_move.end.x == sample_dst3.x && next_move.end.y == sample_dst3.y ){ return NORMAL; }
        else if ( next_move.end.x == sample_dst4.x && next_move.end.y == sample_dst4.y ) { return NORMAL; }
        else {
            /* token is either red_king or white_king but not matach any sample destinations, it's a invalid move */
            printf("Please follow the rule to do the moving\n");
            return INVALID;          
        }
    }


    /* Never return here */
    return NORMAL;
}


/* Requirement  - Tests whether the next player has any valid moves */
BOOLEAN test_for_winner(struct player * next_player, 
        enum cell_contents board[][BOARDWIDTH])
{
    BOOLEAN has_moves = TRUE;
    int i, j;
    enum move_type res;
    Move next_move = {.start.x = 0, .start.y = 0, .end.x = 0, .end.y = 0 };

    if ( next_player->col == P_RED ) {
        for(i=0; i<BOARDWIDTH; i++) {
            for(j=0; j<BOARDHEIGHT; j++) {
                if (board[i][j] == RED || board[i][j] == K_RED) {
                    /* case 1 */
                    if ( i+1 < BOARDWIDTH && j-1 >= MIN_WIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i + 1;
                        next_move.end.y = j - 1;
                        res = is_valid_move(next_move, next_player, board);
                        if( res == NORMAL  ) 
                            break;
                    }

                    /* case 2 */
                    if ( i+1 < BOARDWIDTH  && j+1 < BOARDWIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i + 1;
                        next_move.end.y = j + 1;
                        res = is_valid_move(next_move, next_player, board);
                        if( res == NORMAL ) 
                            break;
                    }

                    /* case 3 */
                    if ( i+2 < BOARDWIDTH && j-2 >= MIN_WIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i + 2;
                        next_move.end.y = j - 2;
                        res = is_valid_move(next_move, next_player, board);
                        if( res == ATTACK  ) 
                            break;
                    }

                    /* case 4 */
                    if ( i+2 < BOARDWIDTH && j+2 < BOARDWIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i + 2;
                        next_move.end.y = j + 2;
                        res = is_valid_move(next_move, next_player, board);
                        if( res == ATTACK ) 
                            break;
                    }

                }

                if ( board[i][j] == K_RED) {

                    /* case 5 */    
                    if ( i-1 >= MIN_WIDTH && j-1 >= MIN_WIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;

                        next_move.end.x = i - 1;
                        next_move.end.y = j - 1;
                        res = is_valid_move(next_move, next_player, board);
                        if( res == NORMAL ) 
                            break;  
                    }

                    /* case 6 */     
                    if ( i-1 >= MIN_WIDTH && j+1 < BOARDWIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i - 1;
                        next_move.end.y = j + 1;
                        res = is_valid_move(next_move, next_player, board);
                        if( res == NORMAL ) 
                            break;    
                    }

                    /* case 7 */
                    if ( i-2 >= MIN_WIDTH && j-2 >= MIN_WIDTH ) {    
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i - 2;
                        next_move.end.y = j - 2;
                        res = is_valid_move(next_move, next_player, board);
                        if( res == ATTACK ) 
                            break;  
                    }

                    /* case 8 */
                    if ( i-2>= MIN_WIDTH && j+2 < BOARDWIDTH) {   
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i - 2;
                        next_move.end.y = j + 2;
                        res = is_valid_move(next_move, next_player, board);
                        if( res == ATTACK ) 
                            break;    
                    }

                }
                if ( j != BOARDHEIGHT ) {
                    break;
                }
            } /* end for */

            if ( i == BOARDWIDTH && j == BOARDHEIGHT ) {
                return FALSE;
            }

        }
    }
    else {
        for(i=0; i<BOARDWIDTH; i++) {
            for(j=0; j<BOARDHEIGHT; j++) {
                if (board[i][j] == WHITE || board[i][j] == K_WHITE) {

                    printf("pos: %d %d\n\n", i, j);
                    /* case 1 */    
                    if ( i-1 >= MIN_WIDTH && j-1 >= MIN_WIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i - 1;
                        next_move.end.y = j - 1;
                        res = is_valid_move(next_move, next_player, board);
                
                        if( res == NORMAL ) 
                            break;  
                    }

                    /* case 2 */   
                    if ( i-1 >= MIN_WIDTH && j+1 < BOARDWIDTH ) {  
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i - 1;
                        next_move.end.y = j + 1;
                        res = is_valid_move(next_move, next_player, board);
                    
                        if( res == NORMAL ) 
                            break;    
                    }

                    /* case 3 */ 
                    if ( i-2 >= MIN_WIDTH && j-2 >= MIN_WIDTH ) {       
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i - 2;
                        next_move.end.y = j - 2;
                        res = is_valid_move(next_move, next_player, board);
                      
                        if( res == ATTACK ) 
                            break;  
                    }

                    /* case 4 */     
                    if ( i-2>= MIN_WIDTH && j+2 < BOARDWIDTH ) {   
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i - 2;
                        next_move.end.y = j + 2;
                        res = is_valid_move(next_move, next_player, board);
                     
                        if( res == ATTACK ) 
                            break;  
                    }

                } /* end if */

                if ( board[i][j] == K_WHITE ) {
                    /* case 1 */
                    if ( i+1 < BOARDWIDTH && j-1 >= MIN_WIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i + 1;
                        next_move.end.y = j - 1;
                        res = is_valid_move(next_move, next_player, board);
                   
                        if( res == NORMAL  ) 
                            break;
                    }

                    /* case 2 */
                    if ( i+1 < BOARDWIDTH && j+1 < BOARDWIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i + 1;
                        next_move.end.y = j + 1;
                        res = is_valid_move(next_move, next_player, board);
                       
                        if( res == NORMAL ) 
                            break;
                    }

                    /* case 3 */
                    if ( i+2 < BOARDWIDTH && j-2 >= MIN_WIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i + 2;
                        next_move.end.y = j - 2;
                        res = is_valid_move(next_move, next_player, board);
                     
                        if( res == ATTACK  ) 
                            break;
                    }


                    /* case 4 */
                    if ( i + 2 < BOARDWIDTH && j + 2 < BOARDWIDTH ) {
                        next_move.start.x = i;
                        next_move.start.y = j;
                        next_move.end.x = i + 2;
                        next_move.end.y = j + 2;
                        res = is_valid_move(next_move, next_player, board);
                       
                        if( res == ATTACK ) 
                            break;
                    }

                } /* end if */

            } /* end nested for */
            if ( j != BOARDHEIGHT ) {
                break;
            }
        } /* end for */
        if ( i == BOARDWIDTH && j == BOARDHEIGHT ) {
            return FALSE;
        }

    }

    return has_moves;
}
