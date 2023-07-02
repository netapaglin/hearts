#include<stdlib.h>/* prints */
#include <stddef.h>  /* size_t */
#include "ui.h"
#include "vector.h"
#include "player.h"
#include "cards.h"
#define SUIT(card) card/NUM_OF_RANK
#define RANK(card) card%NUM_OF_RANK
#define HEART "\xE2\x99\xA5"
#define SPADE "\xE2\x99\xA0"
#define DIAMOND "\xE2\x99\xA6"
#define CLUB "\xE2\x99\xA3"
#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define CYAN "\x1B[36m"



static void PrintSuit(int _suit);
static void PrintRank(int _rank);

void PrintRoundNumber(size_t _num)
{
	printf( " \n " );
	printf( "                   ******************** ROUND NUMBER %ld  *******************", _num );
    printf( " \n " );
}

void PrintTrickNumber(int _num)
{
	printf( " \n " );
	printf( "                       ----------------- trick %d  ----------------", _num );
    printf( " \n " );
}

void PrintCardOnTable(int _card)
{
	int item, rank;
	printf( "\nChosen Card:" );
   	printf( " %d   " , _card);
   	rank = RANK(_card)+2;
 	PrintRank(rank);
   	PrintSuit(SUIT(_card));
    printf( " \n " );
}


void PrintDeckCards(Vector *_vector)
{
	size_t i;
	int item;
	if (_vector == NULL)
	{
		return;
	}
	for ( i=0 ; i < GetVectorNumItems(_vector) ; ++i)
   {
    VectorGet(_vector, i, &item);
   	printf( " %d  , " , item);
   }
    printf( " \n " );
}


void PrintPlayerCards(Vector *_vector)
{
	size_t i;
	int item, rank;
	if (_vector == NULL)
	{
		return;
	}
	 printf( " \n " );
	 printf( "Hand cards - \n " );
	for ( i=0 ; i < GetVectorNumItems(_vector) ; ++i)
   {
    VectorGet(_vector, i, &item);
   	printf( " %d : " , item);
   	rank = RANK(item)+2;
 	PrintRank(rank);
   	PrintSuit(SUIT(item));
   	putchar(' ');
   	putchar('|');
   }
    printf( " \n " );
}

void PrintValidCards(int* _arr , int _length)
{
	int item, rank;
	if (_arr == NULL)
	{
		return;
	}
	printf( "Valid cards - \n " );
	for ( item=0 ; item < _length ; ++item)
   {
   	printf( " %d : " , _arr[item]);
   	rank = RANK(_arr[item])+2;
 	PrintRank(rank);
   	PrintSuit(SUIT(_arr[item]));
   	putchar(' ');
   	putchar('|');
   }
    printf( " \n\n " );
}


void PrintTable(size_t * _tableArr , size_t _numOfPlayers)
{
	size_t i ;
	int cardSuit , cardRank;
	if (_tableArr == NULL)
	{
		return;
	}
	for ( i=0 ; i < _numOfPlayers ; ++i)
   {
   		cardSuit = SUIT(_tableArr[i]);
   		cardRank = RANK(_tableArr[i])+2;
   		printf( " \n " );
   	
   		printf(  " player  %ld -" , i);
   		 switch (cardSuit) {
        case 0:
     	  	 printf(GREEN);
            printf( " %d %s " , cardRank , CLUB);
            printf(NORMAL);
            break;
        case 1:
        	printf(GREEN);
            printf( " %d %s  ", cardRank , SPADE );
            printf(NORMAL);
            break;
        case 2:
        	 printf(RED);
             printf( " %d %s  " , cardRank , DIAMOND);
             printf(NORMAL);
            break;
        case 3:
        	 printf(RED);
             printf( " %d %s " , cardRank, HEART );
             printf(NORMAL);
            break;
   		}
   }
    printf( " \n " );
}


void PrintWhoLostTrick(int _lost)
{
   	printf( " player %d  lost in the trick \n" , _lost);
}

void PrintLostWinGame(int _lost , int _win)
{
   	printf( " Player %d  lost in the game \n\n" , _lost);
  	printf( "                                     ********** THE WINNER IS PLAYER %d ********** \n" , _win);
  	printf("\n");
}

void PrintGameScore(size_t * _scoreArr , size_t _numOfPlayers)
{
	size_t i ;
	if (_scoreArr == NULL)
	{
		return;
	}
    printf(CYAN);
	printf( "\n Game score: \n " );
	for ( i=0 ; i < _numOfPlayers ; ++i)
    {
    	printf(  " player  %ld  - score %ld | " , i ,  _scoreArr[i]);
    }
    printf(NORMAL);
    printf( " \n\n " );
}

void PrintTrickScore(size_t * _scoreArr , size_t _numOfPlayers)
{
	size_t i ;
	if (_scoreArr == NULL)
	{
		return;
	}
	printf( "\n Trick score: \n " );
	for ( i=0 ; i < _numOfPlayers ; ++i)
    {
    	printf(  " player  %ld  - score %ld | " , i ,  _scoreArr[i]);
    }
    printf( " \n " );
}

void PrintSeperateLine()
{
    printf( "\n---------------------------------------------------------------------------------------------------------------------------------------------\n " );
}

static void PrintSuit(int _suit)
{
	switch(_suit){
		case 0:
		    printf(GREEN);
            printf(CLUB);
            printf(NORMAL);
		break;
		case 1:
		    printf(GREEN);
            printf(SPADE);
            printf(NORMAL);
		break;
		case 2:
		    printf(RED);
            printf(DIAMOND);
            printf(NORMAL);
		break;
		case 3:
		    printf(RED);
            printf(HEART);
            printf(NORMAL);
		break;
		}
}

static void PrintRank(int _rank)
{
	switch(_rank){
		case 2:
		    putchar('2');
		break;
		case 3:
		    putchar('3');
		break;
		case 4:
		    putchar('4');
		break;
		case 5:
		    putchar('5');
		break;
		case 6:
		    putchar('6');
		    break;
		case 7:
		    putchar('7');
		break;
		case 8:
		    putchar('8');
		break;
		case 9:
		    putchar('9');
		break;
		case 10:
		   printf("10");
		   break;
		case 11:
		    putchar('J');
		break;
		case 12:
		    putchar('Q');
		break;
		case 13:
		    putchar('K');
		break;
		case 14:
		    putchar('A');
		break;
		default:
		break;
		}
}



