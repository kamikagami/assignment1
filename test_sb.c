#include <stdio.h>
#include "scoreboard.h"



int main(void)
{
	Result res;

	struct result scoreboard[SCOREBOARDSIZE];
	printf("Input name here:\n");
	/*scanf("%s %s", res.won, res.lost );*/
	

	init_scoreboard(scoreboard);
	
	int i;
	
	for( i=0; i<11; i++) {
	  sprintf(res.won, "%d", i);
	  sprintf(res.lost, "-%d", i);	 
	  add_to_scoreboard(scoreboard, &res);
	}
	display_scoreboard(scoreboard);
	
	
	return 0;
}
