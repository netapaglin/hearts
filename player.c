#include<stdlib.h>
#include <stddef.h>  /* size_t */
#include "player.h"
#include "vector.h"
#include "ui.h"
#include "round.h"
#define MAGIC_NUM 65972314
#define ERROR -1
#define NOT_FOUND -2
#define HUMAN 1
#define COMPUTER 2
#define FLAG_ON 1
#define FLAG_OFF 0

static void Swap ( Vector* _vec, size_t _x, size_t _y, int _a, int _b);
PlayerResult BubbleSort (Vector* _vec);



struct Player
{
	Vector *m_vector;
	size_t m_id; 
	int m_type;
	int m_magicNum;
};

Player* PlayerCreate(size_t _size, size_t _blockSize, size_t _id, int _type)
{
	Player * play;
	if (_size == 0 && _blockSize == 0)
	{
		return NULL;
	}
	play = (Player*)malloc (sizeof(Player));
	if (play == NULL)
	{
		return NULL;
	}
	play-> m_vector = VectorCreate(_size, _blockSize);
	if (play -> m_vector == NULL)
	{
		return NULL;
	}
	play-> m_type = _type;
	play-> m_id = _id;
	play-> m_magicNum = MAGIC_NUM;
	return play;
}


PlayerResult InsertCard(Player * _play , int _card)
{
	ADTErr vec;
	if(_play == NULL)
	{
		return PLAYER_UNITIALIZED_ERROR;
	}
	vec =VectorAdd(_play -> m_vector, _card);
	if(vec != ERR_OK) 
	{
		return PLAYER_VECTOR_ERROR;
	}	
	return PLAYER_SUCCESS;
}

int FindCard(Player * _play , size_t _numOfItems ,size_t _card)
{
	int item;
	int index;
	ADTErr vec;
	if (_play == NULL)
	{
		return ERROR;
	}
	for( index = 0 ; index < _numOfItems ; ++index)
	{
		vec = VectorGet(_play -> m_vector ,index, &item);
		if(vec != ERR_OK) 
		{
			return ERROR;
		}	
		if (item == _card)
		{
			return index;
		}
	}
	return NOT_FOUND;
}




int RemoveCard(Player * _play)
{
	int card;
	ADTErr vec;
	if (_play == NULL)
	{
		return ERROR;
	}
	vec = VectorDelete(_play -> m_vector ,&card);
	if(vec != ERR_OK) 
	{
		return ERROR;
	}	
	return card;
}

/****************************************************************************************/
int PutCard(Player * _play , void* _context, size_t* m_table, CheckRules _rules, Strategy _strategy )
{
	int card, index, validResult;
	int choosenCard , humanCard;
	int playerType = _play -> m_type;
	int validCardsIndex = 0 , validCardsInput;
	int vectorLength , count = 0;
	int* validCards;
	if (_play == NULL || _context == NULL || m_table == NULL || _rules == NULL || _strategy == NULL)
	{
		return ERROR;
	}
	VectorItemsNum(_play ->m_vector, &vectorLength);
	validCards = (int*)malloc(vectorLength *sizeof(int));
	if (validCards == NULL)
	{
		return ERROR;
	}
 	switch (playerType) {
        case COMPUTER:
        	for (index = 0; index < vectorLength ;++index )
        	{
        	VectorGet(_play ->m_vector, index , &card);
        	validResult = _rules(_play ->m_vector , card, _context );
        		if(validResult == 1)
        		{
        			validCards[validCardsIndex]= card;
        			validCardsIndex++;
       		 	}
        	}
        	PrintPlayerInfo(_play);
        	choosenCard =_strategy(validCards , validCardsIndex , _context);

            PrintPlayerCards(_play -> m_vector);
            PrintValidCards(validCards , validCardsIndex);
            PrintCardOnTable(choosenCard);
            return choosenCard;
            break;
        case HUMAN:
			for (index = 0; index < vectorLength ;++index )
        	{
        	VectorGet(_play ->m_vector, index , &card);
        	validResult = _rules(_play ->m_vector , card, _context );
        		if(validResult == 1)
        		{
        			validCards[validCardsIndex]= card;
        			validCardsIndex++;
       		 	}
        	}
        	PrintPlayerInfo(_play);
        	PrintPlayerCards(_play -> m_vector);
        	PrintValidCards(validCards , validCardsIndex);
        	validCardsInput = 0;
     	  	while (validCardsInput == 0)
        	{
        	    printf("Enter a card number: ");
   		   		scanf("%d", &humanCard);
   		   		getchar();
   			   	for (index = 0; index < vectorLength ;++index )
        		{
        			if(validCards[index] == humanCard)
        			{
        				validCardsInput = 1;
       			 	}
       			}
   		   		if(validCardsInput == 0)
   		   		{
   		   			printf("Invalid card number. Please try again.\n");
   		   		}
        	}
        	
            printf("You entered: %d\n", humanCard);
        	choosenCard = humanCard;
            return choosenCard;
            break;
	}
}

PlayerResult PrepareCard(Player * _play , int _choosenCard)
{
	int choosenCardIndex, num;
	int vectorLength;
	if (_play == NULL)
	{
		return PLAYER_POINTER_NULL;
	}
	VectorItemsNum(_play ->m_vector, &vectorLength);
	VectorGet(_play ->m_vector, vectorLength -1 , &num);
	choosenCardIndex = FindCard(_play , vectorLength , _choosenCard);
	Swap ( _play ->m_vector, choosenCardIndex , vectorLength -1, _choosenCard, num);
	return PLAYER_SUCCESS;
}


PlayerResult SortCards(Player * _play)
{
	int * arr;
	int vectorLength;
	VectorItemsNum(_play ->m_vector, &vectorLength);
	if (_play == NULL)
	{
		return PLAYER_POINTER_NULL;
	}
	BubbleSort(_play -> m_vector);
	return PLAYER_SUCCESS;
}

void PrintHand(Player * _play)
{
	if (_play == NULL)
	{
		return;
	}
	PrintPlayerCards(_play ->m_vector);
}

void PrintPlayerInfo(Player * _play)
{
	if (_play == NULL)
	{
		return;
	}
	printf("\n");
	if (_play -> m_type == 2)
	{
		printf("id %ld - computer", _play -> m_id);
	}else
	{
		printf("id %ld - you", _play -> m_id);
	}
}

void PlayerDestroy(Player* _play)
{
	if (_play != NULL &&  _play -> m_magicNum != 0)
	{
		 VectorDestroy(_play -> m_vector);
		 free(_play);
		 _play -> m_magicNum =0;
	}
}
/***********************************    BUBBLE SORT  **************************************/


static void Swap ( Vector* _vec, size_t _x, size_t _y, int _a, int _b)
{
	VectorSet ( _vec, _x, _b);
	VectorSet (_vec, _y, _a);
	return;
}


PlayerResult BubbleSort (Vector* _vec)
{
	int numOfElements , allInOrder, a, b;
	size_t y , x , endPointer=1;
	if (_vec == NULL)
	{
		return PLAYER_POINTER_NULL;
	}
	VectorItemsNum(_vec ,&numOfElements);
	if (numOfElements == 0)
	{
		return PLAYER_UNDERFLOW;
	}
	for (y = 0 ; y <= numOfElements; ++y)
	{
		allInOrder = 0;
		for( x = 0 ; x < numOfElements - endPointer ; ++x )
		{
			VectorGet(_vec , x, &a);
			VectorGet(_vec , x +1, &b);
			if (a > b)
			{
				Swap ( _vec, x , x+1, a, b);
				allInOrder = 1;
			}
		}
	}
	++endPointer;
	if(allInOrder == 0)
	{
		return PLAYER_SUCCESS;
	}
	return PLAYER_SUCCESS;
}



size_t GetPlayerId(Player* _play)
{
	return _play -> m_id;
}

int GetPlayerTyped(Player* _play)
{
	return _play -> m_type;
}

int GetPlayerMagicNaum(Player* _play)
{
	return _play -> m_magicNum;
}





