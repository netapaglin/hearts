#include <stdio.h>/* for prints*/
#include "deck.h"
#include "vector.h"
#include "ui.h"

void TestCreateNormal();
void TestCreateSizeZero();
void TestCreateSizeMinus();
void TestCreateCheckMembers();

void TestShuffleNormal();
void TestShuffleNULLInput();
void TestShuffleErrorInput();

void TestGetCardNormal();
void TestGetCardInputNull();

void TestDoubleDestroy();
void TestMagicNum();

int main (void)
{
	
	TestCreateNormal();
	TestCreateSizeZero();
	TestCreateSizeMinus();
	TestCreateCheckMembers();

	TestShuffleNormal();
	TestShuffleNULLInput();
	TestShuffleErrorInput();
	
	TestGetCardNormal();
	TestGetCardInputNull();
	
	TestDoubleDestroy();
	TestMagicNum();
	
	return 1;
}

void TestMagicNum()
{
	Deck*  deck;
	deck = DeckCreate (52, 0);
	 DeckDestroy(deck);
	 if (GetDeckMagicNum(deck) == 0)
	 {
	  	printf("test magic num- PASS\n");
	 }else
	 {
		printf("test magic num- FAIL\n");
	 }
}	


void TestDoubleDestroy()
{
	Deck*  deck;
	deck = DeckCreate (52, 0);
	 DeckDestroy(deck);
	 DeckDestroy(deck);
	 printf("test double destroy - PASS\n");
}	 


void TestGetCardInputNull()
{
	Deck*  deck;
	int x;
	deck = DeckCreate (52, 0);
	 x = GetCard(NULL );
	 if (x == -1)
	 {
	  	printf("test get input NULL- PASS\n");
	 
	 }else
	 {
		printf("test get  input NULL- FAIL\n");
	 }
	 DeckDestroy(deck);
}

void TestGetCardNormal()
{
	Deck*  deck;
	int x;
	deck = DeckCreate (52, 0);
	GetCard(deck );
	 x = GetCard(deck );
	printf(" card %d\n", x);
	 if (x)
	 {
	  	printf("test get card normal- PASS\n");
	 
	 }else
	 {
		printf("test get card normal - FAIL\n");
	 }
	 DeckDestroy(deck);
}


void TestShuffleErrorInput()
{
	Deck*  deck;
	deck = DeckCreate (52, 0);
	
	 if (DeckShuffle(deck , 0) == DECK_INPUT_ERROR)
	 {
	  	printf("test shuffle input error- PASS\n");
	 
	 }else
	 {
		printf("test shuffle input error - FAIL\n");
	 }
	 DeckDestroy(deck);
}

void TestShuffleNULLInput()
{
	Deck*  deck;
	deck = DeckCreate (52, 0);
	
	 if (DeckShuffle(NULL , 52) == DECK_UNITIALIZED_ERROR)
	 {
	  	printf("test shuffle null input- PASS\n");
	 
	 }else
	 {
		printf("test shuffle null input - FAIL\n");
	 }
	  DeckDestroy(deck);
}



void TestShuffleNormal()
{
	Deck*  deck;
	deck = DeckCreate (52, 0);
	
	 if (DeckShuffle(deck , 52) == DECK_SUCCESS)
	 {
	  	printf("test shuffle normal - PASS\n");
	 }else
	 {
		printf("test size zero - FAIL\n");
	 }
	 DeckDestroy(deck);
}


void TestCreateNormal()
{
	Deck*  deck;
	deck = DeckCreate (15, 3);
	 if (deck == NULL)
	 {
	  	printf("test create normal - FAIL\n");
	 }else
	 {
		printf("test  create normal - PASS\n");
	 	DeckDestroy(deck);
	 }
}

void TestCreateCheckMembers()
{
	Deck*  deck;
	deck = DeckCreate (15, 3);
	 if (deck != NULL&&
	GetDeckSize(deck) == 15 &&
	 GetDeckMagicNum(deck) == 59632874 
	 )
	 {
	 	printf("test struct members - PASS\n");
	 }else
	 {
		printf("test struct members - FAIL\n"); 
	 }
	 DeckDestroy(deck);
}

void TestCreateSizeMinus()
{
	Deck*  deck;
	deck = DeckCreate (-1, 3);
	 if (deck != NULL)
	 {
	  	printf("test size minus - FAIL\n");
	 }else
	 {
		printf("test size minus - PASS\n");
	 	DeckDestroy(deck);
	 }
}

void TestCreateSizeZero()
{
	Deck*  deck;
	deck = DeckCreate (0, 3);
	 if (deck != NULL)
	 {
	  	printf("test size zero - FAIL\n");
	 }else
	 {
		printf("test size zero - PASS\n");
	 	DeckDestroy(deck);
	 }
}



