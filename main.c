#include <stdio.h>/* for prints*/
#include "main.h"
#include "game.h"
#include "round.h"
#define HUMAN_PLAYERS 1
#define COMPUTER_PLAYERS 3

int main (void)
{
	Game * play;

	play = GameCreate(HUMAN_PLAYERS , COMPUTER_PLAYERS);
	

	
	RunTheRound(play, CheckWin );

	GameDestroy(play);
	
	return 1;
}
