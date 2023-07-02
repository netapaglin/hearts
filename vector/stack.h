#ifndef __STACK_H__
#define __STACK_H__
#include "ADTDefs.h"

typedef struct Stack Stack;

/*description- this function create a structure of Stack
input- size - array size of strcture
blockSize - the size the array should reallocate in case the allocation had finished
**both of them should be non-negative and only one can be zero, not both.
output- pointer of struct
	           NULL
errors- returns NULL in case size and blockSize both of them equals 0
returns NULL in case there in no memory to allocate a new structure*/
Stack* StackCreate (size_t _size, size_t _blockSize);

/*description- this function deletes a structure of type Stack
input- structure pointer
output - none
errors- in case the pointer is NULL nothing happens.*/
void StackDestroy(Stack* _stack);

/*description- this function adds _item to a structure array of type Stack to the last position
input- _stack- structure pointer
	_item- the number to add to the array
output- ERR_OK
	ERR_POINTER_NULL
errors-ERR_POINTER_NULL - either the pointer or the array equal NULL.*/
ADTErr StackPush (Stack* _stack, int _item);

/*description- this function asign the last value of Vector Stack array 
input- _stack - structure pointer
output- ERR_OK
	ERR_POINTER_NULL
errors- ERR_POINTER_NULL- either the pointer or the array equal NULL. */
ADTErr StackPop (Stack* _stack, int* _item);

/*description- this function removes the last value of the Stack array and assign its value to _item
input- _stack - structure pointer
	_item- pointer to store the deleted value
output- ERR_OK
	ERR_POINTER_NULL
errors- ERR_POINTER_NULL - either the pointer or the array equal NULL.*/
ADTErr StackTop (Stack* _stack, int* _item);

/*description- this function check if the Stack array is empty
input- _stack - structure pointer
output- ERR_FALSE - if it is not empty.
ERR_TRUE - if it is empty.
ERR_POINTER_NULL
errors- ERR_POINTER_NULL - either the pointer or the array equal NULL.*/
int StackIsEmpty(Stack* _stack);

/*description- this function prints a struct of Stack
input-_stack- structure pointer
errors- in case the pointer is NULL nothing happens. */
void StackPrint (Stack *_stack);


#endif /* __STACK__ */
