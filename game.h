#ifndef __GAME_H__
#define __GAME_H__
#include<stdlib.h>
#include "round.h"

typedef int	(*CheckIfWin)(Round * _round);

/*struct of game*/
typedef struct Game Game;

typedef enum Game_Result {
	GAME_SUCCESS,
	GAME_UNITIALIZED_ERROR,				
	GAME_ALLOCATION_ERROR,				
	GAME_INPUT_ERROR
} GameResult;

/*description- this function create a structure of Game
input- _realPlayer - how many human players in the game.
			_mashinPlayer -  how many mashine players in the game.
output- pointer of struct
	           NULL
errors- returns NULL in case the input pointers are equal to NULL.
returns NULL in case there in no memory to allocate a new structure*/
Game* GameCreate (size_t _realPlayer , size_t _mashinPlayer);

/*description- this function run and manage the rounds of the game.
input- _game -structure pointer
			_isWinner -  function pointer.
output- pointer of struct
	           or error
errors- GAME_INPUT_ERROR - in case the input pointer  equal to NULL.*/
GameResult RunTheRound(Game* _game, CheckIfWin _isWinner);

/*description- this function deletes a structure of Game
input- structure pointer
output - none
errors- in case the pointer is NULL nothing happens.*/
void GameDestroy(Game* _game);

#endif /* __GAME_H__ */
