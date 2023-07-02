#ifndef __ROUND_H__
#define __ROUND_H__
#include<stdlib.h>
#include "player.h"


typedef struct Round Round;
typedef struct Parameters Parameters;

typedef enum Round_Result {
	ROUND_SUCCESS,
	ROUND_UNITIALIZED_ERROR,				
	ROUND_ALLOCATION_ERROR,				
	ROUND_INPUT_ERROR,
	ROUND_DEPENDECIES_ERROR
} RoundResult;


/*description- this function create a structure of Round
input- _numOfPlayers - how many players in the game.
			_players - pointer to the struct of the players.
			_score - the score of the game.
output- pointer of struct
	           NULL
errors- returns NULL in case the input pointers are equal to NULL.
returns NULL in case there in no memory to allocate a new structure*/
Round* RoundCreate (size_t _numOfPlayers , Player ** _players, size_t* _score);


/*description- this function run one round of the game
input- _round - structure pointer of Round.
			_roundCounter - .the number of rounds.
output- ROUND_SUCCESS 
				or errors.
errors- ROUND_UNITIALIZED_ERROR if the pointer or the _deck equal NULL.
				 ROUND_UNITIALIZED_ERROR if the allocation of the score array failed.*/
RoundResult RunRound(Round * _round , size_t _roundCounter);

/*description- this function check if one of the player gain more then 100 score.
input- _round - structure pointer of Round.
output- return 1 if there is a winner.
				return 0 if there is no winner yet.
				or ERROR.
errors- ERROR if the pointer or the _deck equal NULL.*/
int CheckWin(Round * _round);


/*description- this function deletes a structure of Round
input- structure pointer
output - none
errors- in case the pointer is NULL nothing happens.*/
void RoundDestroy(Round* _round);

#endif /* __ROUND_H__ */

