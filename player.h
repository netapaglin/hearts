#ifndef __PLAYER_H__
#define __PLAYER_H__
#include "vector.h"



/*strucrt of player*/
typedef struct Player Player;


typedef enum Player_Result {
	PLAYER_SUCCESS,
	PLAYER_UNITIALIZED_ERROR,				
	PLAYER_ALLOCATION_ERROR,				
	PLAYER_INPUT_ERROR,
	PLAYER_POINTER_NULL,
	PLAYER_UNDERFLOW,
	PLAYER_VECTOR_ERROR
} PlayerResult;


typedef int(*CheckRules)(Vector * _vec , int _cardIndex, void* _context );
typedef int (*Strategy)(int* _validCards , int _length , void* _context  );

/*description- this function create a structure of Player
input- size - array size of strcture.
			blockSize - the size the array should reallocate in case the allocation had finished.
			**both of them should be non-negative and only one can be zero, not both.
			id- Id of the plater.
			type-  1 if the player is human, 2 if the player is computer
output- pointer of struct
	           NULL
errors- returns NULL in case there is an error with the Vector functions.
returns NULL in case there in no memory to allocate a new structure*/
Player* PlayerCreate (size_t _size, size_t _blockSize, size_t _id, int _type);

/*description- this function add a card to the player.
input- _play - structure pointer.
			_card - a card number.
output- PLAYER_SUCCESS.
				or errors
errors- PLAYER_UNITIALIZED_ERROR - if the pointer or the _play equal NULL.
	 PLAYER_VECTOR_ERROR if the vector struct return error*/
PlayerResult InsertCard(Player * _play , int _card);

/*description- this function remove the last card to the player's card, and return the value of the removed card.
input- _play - structure pointer.
output- value of the removed card.
				or errors
errors- ERROR - if the pointer or the _play equal NULL.
			 ERROR if the vector struct return error*/
int RemoveCard(Player * _play);

/*description- this function find if a certain card exists in the players card and return the index of the card.
input- _play - structure pointer.
			_numOfItems - number of cards in the player hand
			_card -  the value of the card to look for
output- index of the card if exists, or NOT_FOUND if not exists.
				or errors
errors- ERROR - if the pointer or the _play equal NULL.
			 ERROR if the vector struct return error*/
int FindCard(Player * _play ,size_t _numOfItems , size_t _card);

/*description- this function choose a card from the player hand.
input- _play - structure pointer.
			_context - strcture pointer.
			m_table - pointer of the table card's array.
			_rules - pointer to function.
			_strategy - pointer to structure.
output- int of card number
				or error
errors- ERROR - if the input are equal NULL.
			 ERROR if there are not valid cards*/
int PutCard(Player * _play, void * _context, size_t* m_table, CheckRules _rules, Strategy _strategy );

/*description- this function sort the cards in thr player hand, from small to big.
input- _play - structure pointer.
output-PLAYER_SUCCESS if everithing went well.
			or error
errors-PLAYER_POINTER_NULL - if the _play input equal NULL.*/
PlayerResult SortCards(Player * _play);

/*description- this function put the chosen card at the end of the vector.
input- _play - structure pointer.
			_choosenCard - int of the chosen card
output-PLAYER_SUCCESS if everithing went well.
			or error
errors-PLAYER_POINTER_NULL - if the _play input equal NULL.*/
PlayerResult PrepareCard(Player * _play , int _choosenCard);

/*description- this function print the cards of the Player
input- structure pointer
output - none
errors- in case the pointer is NULL nothing happens.*/
void PrintHand(Player * _play);
void PrintPlayerInfo(Player * _play);


/*description- this function deletes a structure of Player
input- structure pointer
output - none
errors- in case the pointer is NULL nothing happens.*/
void PlayerDestroy(Player* _play);

#endif /* __PLAYER_H__ */
