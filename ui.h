#ifndef __UI_H__
#define __UI_H__
#include "vector.h"
#include "player.h"

/*description- this function print the cards in the deck.
input- Vector struct pointer
output - none
errors- in case the pointer is NULL nothing happens.*/
void PrintDeckCards(Vector *_vector);

/*description- this function print the cards in the player "hand".
input- Vector struct pointer
output - none
errors- in case the pointer is NULL nothing happens.*/
void PrintPlayerCards(Vector *_vector);

/*description- this function print the cards on the table.
input- pointer if the tableArr, and number of players in the game
output - none
errors- in case the pointer is NULL nothing happens.*/
void PrintTable(size_t * _tableArr , size_t _numOfPlayers);

/*description- this function print who lost in the trick.
input- int id of the loser.
output - none
errors- in case the pointer is NULL nothing happens.*/
void PrintWhoLostTrick(int _lost);

/*description- this function print who lost and who win in the game.
input- int id's of the loser and the wiiner.
output - none
errors- in case the pointer is NULL nothing happens.*/
void PrintLostWinGame(int _lost , int _win);

/*description- this function print the score of each player in the trick.
input- pointer if the scoreArr, and number of players in the game
output - none
errors- in case the pointer is NULL nothing happens.*/
void PrintTrickScore(size_t * _scoreArr , size_t _numOfPlayers);

/*description- this function print the valid cardds.
input- pointer if the array, and size of the array
output - none
errors- in case the pointer is NULL nothing happens.*/
void PrintValidCards(int* _arr , int _length);

/*description- this function print the card that the player choose.
input- int of _card.
output - none
errors-none*/
void PrintCardOnTable(int _card);

/*description- this function print trick number.
input- int of _num.
output - none
errors-none*/
void PrintTrickNumber(int _num);

/*description- this function print round number.
input-size_t of _num.
output - none
errors-none*/
void PrintRoundNumber(size_t _num);

/*description- this function print the score of each player in the Game.
input- pointer if the scoreArr, and number of players in the game
output - none
errors- in case the pointer is NULL nothing happens.*/
void PrintGameScore(size_t * _scoreArr , size_t _numOfPlayers);

/* Seperate Line*/
void PrintSeperateLine();

#endif /* __UI_H__ */
