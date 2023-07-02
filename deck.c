#include <stdio.h>/* for prints*/
#include<stdlib.h>/* size_t malloc srand*/
#include<time.h>/* srand*/
#include "deck.h"
#include "vector.h"
#include "cards.h"
#include "round.h"
#include "ui.h"
#define MAGIC_NUM 59632874
#define ERROR -1

static void Swap(int index, Vector* _deck , size_t _size);

struct Deck
{
	Vector *m_vector;
	int m_magicNum;
	size_t m_size;
};

Deck* DeckCreate (const size_t _size, const size_t _blockSize)
{
	Vector * v;
	int index;
	ADTErr vec;
	Deck * deck;
	srand(time(NULL));
	if (_size == 0)
	{
		return NULL;
	}
	deck = (Deck*)malloc (sizeof(Deck));
	v = VectorCreate(_size,  _blockSize);
	if (v == NULL)
	{
		free(deck);
		return NULL;
	}
	deck-> m_magicNum = MAGIC_NUM;
	deck -> m_size = _size;
	deck-> m_vector = v;
	for(index = 0 ; index < _size ; ++index)
	{
		vec = VectorAdd(v , index);
		if(vec != ERR_OK) 
		{
			return NULL;
		}
	}	
	DeckShuffle(deck , _size);	
	return deck;
}

DeckResult DeckShuffle(const Deck*  _deck , const size_t _size)
{
	int index;
	
	if(_deck  == NULL)
	{
		return DECK_UNITIALIZED_ERROR;
	}
	if(_size == 0)
	{
		return DECK_INPUT_ERROR;
	}
    for(index = 0 ; index < _size; ++index)
    {
    	Swap(index,  _deck -> m_vector ,  _size);
	}
	return DECK_SUCCESS;
}

int GetCard(const Deck * _deck )
{
	int card;
	ADTErr vec;
	if (_deck == NULL)
	{
		return ERROR;
	}
	vec = VectorDelete(_deck -> m_vector, &card);
	if(vec != ERR_OK) 
	{
		return vec;
	}
	return card;
}

static void Swap(int _index, Vector* _deck , size_t _size)
{
	int num , numValue;
	int item;
	num = (rand() % (_size));
	VectorGet(_deck, _index, &item);
	VectorGet(_deck, num, &numValue);
	VectorSet(_deck, _index, numValue);
    VectorSet(_deck, num, item);
}

void DeckDestroy(Deck* _deck)
{
	if (_deck != NULL &&  _deck -> m_magicNum != 0)
	{
		 VectorDestroy(_deck -> m_vector);
		 free(_deck);
		 _deck -> m_magicNum =0;
	}
}

size_t GetDeckSize(Deck * _deck)
{
	return _deck -> m_size;
}

size_t  GetDeckMagicNum(Deck * _deck)
{
	return _deck -> m_magicNum;
}


