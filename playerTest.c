#include <stdio.h>/* for prints*/
#include "player.h"
#include "vector.h"
#include "ui.h"

void TestCreateNormal();
void TestCreateSizeZero();
void TestCreateCheckMembers();

void TestInsertCardNormal();
void TestInsertInsertNull();

void TestFindCardInputNULL();
void TestFindCardINotFound();

void TestRemoveCardInputNull();

void TestPlayerDestroyMagicNum();
void TestPlayerDoubleDestroy();


int main (void)
{
	TestCreateNormal();
	TestCreateSizeZero();
	TestCreateCheckMembers();
	
	TestInsertCardNormal();
	TestInsertInsertNull();
	
	TestFindCardInputNULL();
/*	TestFindCardINotFound();*/

    TestRemoveCardInputNull();
    
    TestPlayerDestroyMagicNum();
	TestPlayerDoubleDestroy();
	return 1;
}


void TestPlayerDoubleDestroy()
{
	Player * play;
	int x;
	play = PlayerCreate (15, 3, 2, 2);
	PlayerDestroy(play);
	PlayerDestroy(play);
	printf("test  double destroy - PASS\n");
} 



void TestPlayerDestroyMagicNum()
{
	Player * play;
	int x;
	play = PlayerCreate (15, 3, 2, 2);
	PlayerDestroy(play);
	 if (GetPlayerMagicNaum(play)==  0 )
	 {
	  	printf("test destroy magic num - PASS\n");
	 }else
	 {
		printf("test destroy magic num - FAIL\n");
	 }
	  PlayerDestroy(play);
} 


void TestRemoveCardInputNull()
{
	Player * play;
	int x;
	play = PlayerCreate (15, 3, 2, 2);
	x = RemoveCard(NULL);
	 if (x ==  -1 )
	 {
	  	printf("test remove card input null - PASS\n");
	 }else
	 {
		printf("test remove card input null - FAIL\n");
	 }
	  PlayerDestroy(play);
} 


void TestFindCardINotFound()
{
	Player * play;
	int x;
	play = PlayerCreate (15, 3, 2, 2);
	x = FindCard(play ,15 , -6 );
	 if (x !=  -2 )
	 {
	  	printf("test find card input not found - PASS\n");
	 }else
	 {
		printf("test  find card  input not found - FAIL\n");
	 }
	  PlayerDestroy(play);
}

void TestFindCardInputNULL()
{
	Player * play;
	int x;
	play = PlayerCreate (15, 3, 2, 2);
	x = FindCard(NULL ,15 , 2 );
	 if (x == -1 )
	 {
	  	printf("test find card input null- PASS\n");
	 }else
	 {
		printf("test  find card  input null - FAIL\n");
	 }
	  PlayerDestroy(play);
}

void TestInsertInsertNull()
{
	Player * play;
	play = PlayerCreate (15, 3, 2, 2);
	 if (InsertCard(NULL , 35) == PLAYER_UNITIALIZED_ERROR )
	 {
	  	printf("test insert NULL - PASS\n");
	 }else
	 {
		printf("test  insertNULL - FAIL\n");
	 }
	  PlayerDestroy(play);
}

void TestInsertCardNormal()
{
	Player * play;
	play = PlayerCreate (15, 3, 2, 2);
	 if (InsertCard(play , 35) == PLAYER_SUCCESS )
	 {
	  	printf("test insert card normal - PASS\n");
	 }else
	 {
		printf("test  insert card normal - FAIL\n");
	 }
	  PlayerDestroy(play);
}

void TestCreateCheckMembers()
{
	Player * play;
	play = PlayerCreate (15, 3, 2, 2);
	 if (play != NULL &&
	 GetPlayerId(play) == 2 &&
	 GetPlayerTyped(play) == 2 &&
	 GetPlayerMagicNaum(play) != 0
	 )
	 {
	  	printf("test create check members - PASS\n");
	 }else
	 {
		printf("test  create check members- FAIL\n");
	 }
	  PlayerDestroy(play);
}


void TestCreateSizeZero()
{
	Player * play;
	play = PlayerCreate (0, 0, 2, 2);
	 if (play == NULL)
	 {
	  	printf("test create size 0 - PASS\n");
	 }else
	 {
		printf("test  create size 0- FAIL\n");
	 }
	  PlayerDestroy(play);
}

void TestCreateNormal()
{
	Player * play;
	play = PlayerCreate (13, 0, 2, 2);
	 if (play == NULL)
	 {
	  	printf("test create normal - FAIL\n");
	 }else
	 {
		printf("test  create normal - PASS\n");
	 PlayerDestroy(play);
	 }
}
