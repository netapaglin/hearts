#include <stdio.h>
#include<stdlib.h>
#include "vector.h"
#include "ADTDefs.h"
#define SIZE 4
#define BLOCK_SIZE 2
#define MAGIC_NUM 98765432


size_t GetVectorSize(Vector *_vector);
size_t GetVectorOriginalSize(Vector *_vector);
size_t GetVectorNumItems(Vector *_vector);
size_t GetVectorBlockSize(Vector *_vector);
int GetVectorMagicNum(Vector *_vector);
/*size_t GetVectorItems(Vector *_vector);*/


void TestAddNullPtr();
void TestAddWorkNormal();
void TestCreateZero();
void TestCreateBlockSizeZero();
void TestCreateVectorMinusOne();
void TestCreateVectorZero();
void TestCreateCheckMembers();

void TestDestroyMagicNum();
void TestDestroy();
void TestDestroyNull();
void TestDoubleFree();

void TestAddWithoutRealloc();
void TestAddWithRealloc();
void TestAddWithBlockSizeZero();
/*void TestAddWithBlockSizeMinus();*/

void TestDellNullPtr();
void TestDellNullNum();
void TestDellNormal();
void TestDellreturnNum();
void TestDellWithoutRealloc();
void TestDellWithRealloc();
void TestDellMoreThanOriginalSize();
void TestDellUnderFlow();

void TestGetCorrectInput();
void TestGetNullInput();
void TestGetWrongIndex();
void TestGetNoInput();

void TestSetCorrectInput();
void TestSetNullInput();
void TestSetWrongIndex();
void TestNoInput();

void TestNumberOfElements();
void TestNumberOfElementsNULLInput();

int main (void)
{

/**** VectorCreate ****/
TestCreateZero();
TestCreateBlockSizeZero();
TestCreateVectorMinusOne();
TestCreateVectorZero();
TestCreateCheckMembers();

/**** VectorDestroy ****/
TestDestroyMagicNum();
TestDestroy();
TestDestroyNull();
TestDoubleFree();

/**** VectorAdd ****/
TestAddNullPtr();
TestAddWorkNormal();
TestAddWithoutRealloc();
 TestAddWithRealloc();
TestAddWithBlockSizeZero();
/*TestAddWithBlockSizeMinus();*/

/**** VectorDelete ****/
TestDellNullPtr();
TestDellNullNum();
TestDellNormal();
TestDellreturnNum();
TestDellWithoutRealloc();
TestDellWithRealloc();
TestDellMoreThanOriginalSize();
TestDellUnderFlow();

/**** VectorGet ****/
TestGetCorrectInput();
TestGetNullInput();
TestGetWrongIndex();
TestGetNoInput();

/**** VectorSet ****/
TestSetCorrectInput();
TestSetNullInput();
TestSetWrongIndex();
TestNoInput();

/**** VectorNumberOfElements ****/
TestNumberOfElements();
TestNumberOfElementsNULLInput();

/*
int  item ;
int index = 3;
int num = 18;
int numOfItems;
 Vector * structPtr;
TestDestroyCheckMembers();
TestCreateZero(structPtr);
 structPtr  =  VectorCreate(SIZE, BLOCK_SIZE );
VectorAdd(structPtr, 1);
VectorAdd(structPtr, 2);
VectorAdd(structPtr, 3);
VectorAdd(structPtr, 4);
VectorAdd(structPtr, 5);
VectorGet(structPtr, index, &item);
VectorItemsNum(structPtr, &numOfItems);
printf("inumOfItems :  %d\n" , numOfItems);
VectorPrint(structPtr);
 VectorDelete(structPtr , &item);
 VectorDelete(structPtr , &item);
VectorPrint(structPtr);
VectorItemsNum(structPtr, &numOfItems);
printf("inumOfItems :  %d\n" , numOfItems);
VectorDestroy(structPtr);
      */
 
	return ERR_OK;
}


void TestCreateZero()
{
 Vector *  vec;
	 vec = VectorCreate(0 , 0 );
	 if (vec == NULL)
	 {
	 	printf("test both parameter zero - PASS\n");
	 }else
	 {
	 	printf("test both parameter zero - FAIL\n");
	 	VectorDestroy(vec);
	 }
}

void TestCreateVectorMinusOne()
{
 Vector *  vec;
	 vec = VectorCreate(-1 ,0 );
	 if (vec == NULL)
	 {
	 	printf("test vector minus 1 - PASS\n");
	 }else
	 {
	 	printf("test  vector minus 1 - FAIL\n");
	 	VectorDestroy(vec);
	 }
}

void TestCreateBlockSizeZero()
{
 Vector *  vec;
	 vec = VectorCreate(5 ,0 );
	 if (vec == NULL)
	 {
	  	printf("test block size zero - FAIL\n");
	 }else
	 {
		printf("test block size zero - PASS\n");
	 	VectorDestroy(vec);
	 }
}

void TestCreateVectorZero()
{
 Vector *  vec;
	 vec = VectorCreate(0 , 5);
	 if (vec == NULL)
	 {
	  	printf("test vector zero - FAIL\n");
	 }else
	 {
		printf("test vector  zero - PASS\n");
	 	VectorDestroy(vec);
	 }
}


void TestCreateCheckMembers()
{
 Vector *  vec;
	 vec = VectorCreate(10 , 5);
	 if (vec != NULL &&
	  GetVectorSize(vec) == 10 &&
	  GetVectorOriginalSize(vec) == 10 &&
	  GetVectorBlockSize(vec) == 5 &&
	  GetVectorNumItems(vec) == 0 &&
	  GetVectorMagicNum(vec)  ==  MAGIC_NUM
	   )
	 {
	 	printf("test struct members - PASS\n");
	  	VectorDestroy(vec);
	 }else
	 {
		printf("test struct members - FAIL\n"); 
	 }
}

void TestDestroyMagicNum()
{
	 Vector *  vec ;
	 vec = VectorCreate(4 ,2 );
	VectorDestroy(vec);
	
	 if (GetVectorMagicNum(vec) == 0  )
	 {
	 printf("test destroy magicNum - PASS\n");
	 
	 }else
	 {
	 	printf("test destroy magicNum - FAIL\n"); 
	 }
}

void TestDestroy()
{
	int numOfItems;
	 Vector *  vec ;
	vec = VectorCreate(4 ,2 );
	VectorDestroy(vec);
	VectorItemsNum(vec, &numOfItems);
	 if (numOfItems == 0 )
	 {
	 printf("test destroy - PASS\n");
	 
	 }else
	 {
	 	printf("test destroy input null - FAIL\n"); 
	 }
}

void TestDestroyNull()
{
	VectorDestroy(NULL);
	 printf("test destroy NULL - PASS\n");
}

void TestDoubleFree()
{
    Vector *  vec ;
	vec = VectorCreate(4 ,2 );
	VectorDestroy(vec);
	VectorDestroy(vec);
	printf("test double free - PASS\n");
	
}



void TestAddNullPtr()
{
	 int  vec;
 	Vector * create;
     create = VectorCreate(2 , 5);
	 vec = VectorAdd(NULL, 2);
	 if (vec == ERR_NOT_INITIALIZED)
	 {
	 	printf("test add pointer NULL - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test  vector minus 1 - FAIL\n");
	 	VectorDestroy(create);
	 }
}

void TestAddWorkNormal()
{
	 int  vec;
 	Vector * create;
     create = VectorCreate(2 , 5);
	 vec = VectorAdd(create , 5);
	 if (vec == ERR_OK)
	 {
	 	printf("test add works normal - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("ttest add works normal - FAIL\n");
	 	VectorDestroy(create);
	 }
}

void TestAddWithoutRealloc()
{
 	Vector * create;
     create = VectorCreate(5 , 2);
     VectorAdd(create , 1);
     VectorAdd(create , 2);
     VectorAdd(create , 3);
	 if (create != NULL &&
	  GetVectorSize(create ) == 5 &&
	  GetVectorOriginalSize(create ) == 5 &&
	  GetVectorBlockSize(create ) == 2 &&
	  GetVectorNumItems(create ) == 3 &&
	  GetVectorMagicNum(create )  ==  MAGIC_NUM 
	   )
	 {
	 	printf("test add without realloc - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test add without realloc - FAIL\n");
	 	VectorDestroy(create);
	 }
}

void TestAddWithRealloc()
{
 	Vector * create;
     create = VectorCreate(4 , 2);
     VectorAdd(create , 1);
     VectorAdd(create , 2);
     VectorAdd(create , 3);
     VectorAdd(create , 4);
     VectorAdd(create , 5);
     VectorAdd(create , 6);
      VectorAdd(create , 7);
	 if (create != NULL &&
	  GetVectorSize(create ) == 8 &&
	  GetVectorOriginalSize(create ) == 4 &&
	  GetVectorBlockSize(create ) == 2 &&
	  GetVectorNumItems(create ) == 7 &&
	  GetVectorMagicNum(create )  ==  MAGIC_NUM 
	   )
	 {
	 	printf("test add with realloc - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test add with realloc - FAIL\n");
	 	VectorDestroy(create);
	 }
}

void TestAddWithBlockSizeZero()
{
	int resault;
 	Vector * create;
     create = VectorCreate(2 , 0);
     VectorAdd(create , 1);
     VectorAdd(create , 2);
      resault =  VectorAdd(create , 3);
	 if (resault == ERR_OVERFLOW )
	 {
	 	printf("test ERR_OVERFLOW - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test ERR_OVERFLOW - FAIL\n");
	 	VectorDestroy(create);
	 }
}

/*
void TestAddWithBlockSizeMinus()
{
	int resault;
 	Vector * create;
     create = VectorCreate(2 , -1);
      resault =  VectorAdd(create , 3);
	 if (resault == ERR_ALLOCATION_FAILED )
	 {
	 	printf("test ERR_ALLOCATION_FAILED - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test ERR_ALLOCATION_FAILED - FAIL\n");
	 	VectorDestroy(create);
	 }
}*/


void TestDellNullPtr()
{
	 int  vec , item;
 	Vector * create;
     create = VectorCreate(2 , 5);
	 VectorAdd(create, 1);
	 VectorAdd(create, 2);
	 vec = VectorDelete(NULL  , &item);
	 if (vec == ERR_NOT_INITIALIZED)
	 {
	 	printf("test del pointer NULL - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test  del pointer NULL1 - FAIL\n");
	 	VectorDestroy(create);
	 }
}

void TestDellNullNum()
{
	 int  vec , item;
 	Vector * create;
     create = VectorCreate(2 , 5);
	 VectorAdd(create, 1);
	 VectorAdd(create, 2);
	 vec = VectorDelete(create   , NULL);
	 if (vec == ERR_NOT_INITIALIZED)
	 {
	 	printf("test del number  NULL - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test  del number NULL1 - FAIL\n");
	 	VectorDestroy(create);
	 }
}

void TestDellNormal()
{
	 int  vec , item;
 	Vector * create;
     create = VectorCreate(2 , 5);
	 VectorAdd(create, 1);
	 VectorAdd(create, 2);
	 vec = VectorDelete(create , &item);
	 if (vec == ERR_OK)
	 {
	 	printf("test del works normal - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test  del works normal - FAIL\n");
	 	VectorDestroy(create);
	 }
}

void TestDellreturnNum()
{
	 int  vec , item;
 	Vector * create;
     create = VectorCreate(2 , 5);
	 VectorAdd(create, 1);
	 VectorAdd(create, 2);
	 vec = VectorDelete(create , &item);
	 if (item == 2)
	 {
	 	printf("test del return num - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test  del return num - FAIL\n");
	 	VectorDestroy(create);
	 }
}


void TestDellWithoutRealloc()
{
 	Vector * create;
 	int item;
    create = VectorCreate(4, 2);
    VectorAdd(create , 1);
    VectorAdd(create , 2);
    VectorAdd(create , 3);
    VectorDelete(create , &item);
     
	 if (create != NULL &&
	  GetVectorSize(create ) == 4 &&
	  GetVectorOriginalSize(create ) == 4 &&
	  GetVectorBlockSize(create ) == 2 &&
	  GetVectorNumItems(create ) == 2 &&
	  GetVectorMagicNum(create )  ==  MAGIC_NUM 
	   )
	 {
	 	printf("test dell without realloc - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test dell  without realloc - FAIL\n");
	 	VectorDestroy(create);
	 }
}

void TestDellWithRealloc()
{
 	Vector * create;
 	int item;
    create = VectorCreate(4, 2);
    VectorAdd(create , 1);
    VectorAdd(create , 2);
    VectorAdd(create , 3);
    VectorAdd(create , 4);
    VectorAdd(create , 5);
    VectorAdd(create , 6);
    VectorAdd(create , 7);
    VectorAdd(create , 8);
   VectorAdd(create , 9);
  
    VectorDelete(create , &item);
	VectorDelete(create , &item);
    VectorDelete(create , &item);
	VectorDelete(create , &item);
	VectorDelete(create , &item);
	 if (create != NULL &&
	  GetVectorSize(create ) == 6 &&
	  GetVectorOriginalSize(create ) == 4 &&
	  GetVectorBlockSize(create ) == 2 &&
	  GetVectorNumItems(create ) ==4 &&
	  GetVectorMagicNum(create )  ==  MAGIC_NUM 
	   )
	 {
	 	printf("test dell with realloc - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test dell  with realloc - FAIL\n");
	 	VectorDestroy(create);
	 }
}


void TestDellMoreThanOriginalSize()
{
 	Vector * create;
 	int item;
    create = VectorCreate(3, 1);
    VectorAdd(create , 1);
    VectorAdd(create , 2);
    VectorAdd(create , 3);
    VectorAdd(create , 4);
	VectorAdd(create , 5);

    VectorDelete(create , &item);
	VectorDelete(create , &item);
    VectorDelete(create , &item);
	VectorDelete(create , &item);

	 if (create != NULL &&
	  GetVectorSize(create ) == 3 &&
	  GetVectorOriginalSize(create ) == 3 &&
	  GetVectorBlockSize(create ) == 1 &&
	  GetVectorNumItems(create ) == 1 &&
	  GetVectorMagicNum(create )  ==  MAGIC_NUM 
	   )
	 {
	 	printf("test dell more then original size - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test dell  more then original size - FAIL\n");
	 	VectorDestroy(create);
	 }
}

void TestDellUnderFlow()
{
 	Vector * create;
 	 int  item;
    create = VectorCreate(1, 0);
    VectorAdd(create , 1);
    VectorDelete(create , &item);
	 if (VectorDelete(create , &item) == ERR_UNDERFLOW)
	 {
	 	printf("test dell ERR_UNDERFLOW - PASS\n");
	 	VectorDestroy(create);
	 }else
	 {
	 	printf("test dell  ERR_UNDERFLOW - FAIL\n");
	 	VectorDestroy(create);
	 }
}

void TestGetCorrectInput()
{
 	Vector *  vec;
 	int item;
 	vec= VectorCreate(5, 2);
    VectorAdd(vec , 1);
    VectorAdd(vec , 2);
    VectorAdd(vec, 3);        
	 VectorGet(vec, 1, &item);
	 if (item == 2)
	 {
	 	printf("test Get correct input - PASS\n");
	 }else
	 {
	 	printf("test Get correct input- FAIL\n");
	 	VectorDestroy(vec);
	 }
}

void TestGetNullInput()
{
 	Vector *  vec;
 	int item;
 	vec= VectorCreate(5, 2);
    VectorAdd(vec , 1);
	 if (VectorGet(NULL, 1, &item) == ERR_NOT_INITIALIZED)
	 {
	 	printf("test Get NULL input - PASS\n");
	 }else
	 {
	 	printf("test Get NULL input- FAIL\n");
	 	VectorDestroy(vec);
	 }
}

void TestGetWrongIndex()
{
 	Vector *  vec;
 	int item;
 	vec= VectorCreate(5, 2);
    VectorAdd(vec , 1);
	 if (VectorGet(vec, 6, &item) == ERR_WRONG_INPUT)
	 {
	 	printf("test Get  wrong index- PASS\n");
	 }else
	 {
	 	printf("test Get wrong index- FAIL\n");
	 	VectorDestroy(vec);
	 }
}

void TestGetNoInput()
{
 	Vector *  vec;
 	int item;
 	vec= VectorCreate(5, 2);
	 if (VectorGet(vec, 2, &item) == ERR_WRONG_INPUT)
	 {
	 	printf("test Get  no Input- PASS\n");
	 }else
	 {
	 	printf("test Get no Input- FAIL\n");
	 	VectorDestroy(vec);
	 }
}

void TestSetCorrectInput()
{
 	Vector *  vec;
 	int item;
 	vec= VectorCreate(5, 2);
    VectorAdd(vec , 1);
    VectorAdd(vec , 2);
    VectorAdd(vec, 3);        
	VectorSet(vec, 1, 15);
	 VectorGet(vec, 1, &item) ;
	 if ( item  == 15)
	 {
	 	printf("test Set correct input - PASS\n");
	 }else
	 {
	 	printf("test Set correct input- FAIL\n");
	 	VectorDestroy(vec);
	 }
}

void TestSetNullInput()
{
 	Vector *  vec;
 	int item;
 	vec= VectorCreate(5, 2);
    VectorAdd(vec , 1);
    VectorAdd(vec , 2);
    VectorAdd(vec, 3);        
	 if ( VectorSet(NULL, 1, 15) == ERR_NOT_INITIALIZED)
	 {
	 	printf("test Set NULL input - PASS\n");
	 }else
	 {
	 	printf("test Set NULL input- FAIL\n");
	 	VectorDestroy(vec);
	 }
}


void TestSetWrongIndex()
{
 	Vector *  vec;
 	int item;
 	vec= VectorCreate(5, 2);
    VectorAdd(vec , 1);    
	 if ( VectorSet(vec, 5, 15) == ERR_WRONG_INPUT)
	 {
	 	printf("test Set wrong index - PASS\n");
	 }else
	 {
	 	printf("test Set wrong index- FAIL\n");
	 	VectorDestroy(vec);
	 }
}


void TestNoInput()
{
 	Vector *  vec;
 	int item;
 	vec= VectorCreate(5, 2);
	 if ( VectorSet(vec, 5, 15) == ERR_WRONG_INPUT)
	 {
	 	printf("test Set no input - PASS\n");
	 }else
	 {
	 	printf("test Set no input- FAIL\n");
	 	VectorDestroy(vec);
	 }
}

void TestNumberOfElements()
{
 	Vector *  vec;
 	int numOfItems;
 	vec= VectorCreate(5, 2);
    VectorAdd(vec , 1);
    VectorAdd(vec , 2);
    VectorAdd(vec, 3);   
    VectorItemsNum(vec, &numOfItems);
	 if ( numOfItems == 3)
	 {
	 	printf("test numOfItems - PASS\n");
	 }else
	 {
	 	printf("test numOfItems - FAIL\n");
	 	VectorDestroy(vec);
	 }
}


void TestNumberOfElementsNULLInput()
{
 	Vector *  vec;
 	int numOfItems;
 	vec= VectorCreate(5, 2);
    VectorAdd(vec , 1);
    VectorAdd(vec , 2);
    VectorAdd(vec, 3);   
	 if ( VectorItemsNum(NULL, &numOfItems) == ERR_NOT_INITIALIZED)
	 {
	 	printf("test numOfItems NULL Input - PASS\n");
	 }else
	 {
	 	printf("test numOfItems  NULL Input  - FAIL\n");
	 	VectorDestroy(vec);
	 }
}
