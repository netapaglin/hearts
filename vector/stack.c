#include <stdio.h>
#include<stdlib.h>
#include "ADTDefs.h"
#include "stack.h"
#include "vector.h"
#define MAGIC_NUM 96385274

struct Stack
{
	Vector *m_vector;
	int m_magicNum;
};

int GetStackMagicNum(Stack* _stack )
{
	return _stack  -> m_magicNum;
}



Stack* StackCreate (size_t _size, size_t _blockSize)
{
	Stack * stack;
	int * temp;
	if (_size == 0 && _blockSize == 0)
	{
		return NULL;
	}
	stack = (Stack*)malloc (sizeof(Stack));
	if (stack == NULL)
	{
		return NULL;
	}
	stack-> m_magicNum = MAGIC_NUM;
	stack-> m_vector = VectorCreate(_size, _blockSize);
	return stack;
}

void StackDestroy(Stack* _stack)
{
	if (_stack != NULL &&  _stack -> m_magicNum != 0)
	{
		 VectorDestroy(_stack-> m_vector);
		 free(_stack);
		 _stack -> m_magicNum =0;
	}
}

ADTErr StackPush (Stack* _stack, int _item)
{
	if (_stack == NULL)
	{
		return ERR_POINTER_NULL;
	}
	return VectorAdd(_stack -> m_vector , _item);
}

void StackPrint (Stack *_stack)
{
	if (_stack != NULL)
	{
		VectorPrint(_stack -> m_vector );
	}
}

ADTErr StackPop (Stack* _stack, int* _item)
{

	int popNum;

	if (_stack == NULL || _item == NULL)
	{
		return ERR_POINTER_NULL;
	}
	VectorDelete( _stack -> m_vector , &popNum);
	*_item = popNum;
	
	return ERR_OK;
}

ADTErr StackTop (Stack* _stack, int* _item)
{
	int 	index ;
	int topNum , indexNum;
	if (_stack == NULL || _item == NULL)
	{
		return ERR_POINTER_NULL;
	}
	
	index = VectorItemsNum(_stack -> m_vector , _item);
	VectorGet(_stack -> m_vector , index, &topNum);
	return ERR_OK;
}

int StackIsEmpty(Stack* _stack)
{

	int numOfItems ;
	
	if (_stack == NULL)
	{
		return ERR_POINTER_NULL;
	}
	VectorItemsNum(_stack -> m_vector , &numOfItems);
	
	if ( numOfItems > 0)
	{
	return ERR_FALSE;
	}
	
	return ERR_TRUE;
}

















