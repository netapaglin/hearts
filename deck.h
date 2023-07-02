#ifndef __DECK_H__
#define __DECK_H__
#include "vector.h"


/*struct of deck*/
typedef struct Deck Deck;

typedef enum Deck_Result {
	DECK_SUCCESS,
	DECK_UNITIALIZED_ERROR,				
	DECK_ALLOCATION_ERROR,				
	DECK_INPUT_ERROR,
	DECK_VECTOR_ERROR
} DeckResult;


/*description- this function create a structure of Deck
input- size - array size of strcture, can not be zero.
blockSize - the size the array should reallocate in case the allocation had finished
output- pointer of struct
	           NULL
errors- returns NULL in case there is an error with the Vector functions.
returns NULL in case there in no memory to allocate a new structure*/
Deck* DeckCreate (const size_t _size, const size_t _blockSize);


/*description- this function shuffle the cards of the deck.
input- _deck - structure pointer
	_size- the amount of elements in the deck.
output- DECK_SUCCESS
				or errors
errors- DECK_UNITIALIZED_ERROR - if the pointer or the _deck equal NULL.
	DECK_INPUT_ERROR  - if the _size input is 0.*/
DeckResult DeckShuffle(const Deck*  _deck , const size_t _size);

/*description- extract the last value of the array , and remove it from the array.
input- _deck - structure pointer
output- the lat value of the array.
				or errors
errors- ERROR - if the pointer or the _deck equal NULL.
	 Vector struct error, according to the Vactor errors file*/
int GetCard(const Deck * _deck );

/*description- this function deletes a structure of Deck
input- structure pointer
output - none
errors- in case the pointer is NULL nothing happens.*/
void DeckDestroy(Deck* _deck);


#endif /* __DECK_H__ */
