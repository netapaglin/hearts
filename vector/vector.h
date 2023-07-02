#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <stdio.h>
#include<stdlib.h>
#include "ADTDefs.h"

typedef struct Vector Vector;

/*description- this function create a structure of Vector
input- size - array size of strcture
blockSize - the size the array should reallocate in case the allocation had finished
**both of them should be non-negative and only one can be zero, not both.
output- pointer of struct
	           NULL
errors- returns NULL in case size and blockSize both of them equals 0
returns NULL in case there in no memory to allocate a new structure*/
Vector* VectorCreate(size_t _initialSize, size_t _extensionBlockSize);


/*description- this function adds _item to a structure array of type Vector to the last position
input- _vector - structure pointer
	_item- the number to add to the array
output- ERR_OK
	ERR_NOT_INITIALIZED
	ERR_OVERFLOW
	ERR_ALOCATION_FAILED
errors- ERR_NOT_INITIALIZED - either the pointer or the array equal NULL.
	ERR_ALOCATION_FAILED there was not enough memory to allocate new value to the array
	ERR_OVERFLOW - in case the array is full and blockSize is 0*/
ADTErr VectorAdd(Vector *_vector, int _item);

/*description- this function removes the last value of the struct array and assign its value to _item
input- _vector - structure pointer
	_item- pointer to store the deleted value
output- ERR_OK
	ERR_NOT_INITIALIZED
	ERR_UNDERFLOW
errors- ERR_NOT_INITIALIZED - either the pointer or the array equal NULL.
	ERR_UNDERFLOW - in case the array is empty*/
ADTErr VectorDelete(Vector *_vector, int* _item);


/*description- this function deletes a structure of type Vector
input- structure pointer
output - none
errors- in case the pointer is NULL nothing happens.*/
void VectorDestroy(Vector* _vector);


/*description- this function get the value of Vector struct array in _index to _item
input- _vector - structure pointer
	_index- the position of the wanted value
	_item- pointer to store the value
output- ERR_OK
	ERR_NOT_INITIALIZED
	ERR_WRONG_INDEX
errors- ERR_NOT_INITIALIZED - either the pointer or the array equal NULL.
	ERR_WRONG_INDEX - the _index is not in the correct range (0 <= _index <=numOfItems-1) */
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);

/*description- this function asign the value of _item to Vector struct array in _index
input- _vector - structure pointer
	_index- the position of the wanted change
	_item- value to store
output- ERR_OK
	ERR_NOT_INITIALIZED
	ERR_WRONG_INDEX
errors- ERR_NOT_INITIALIZED - either the pointer or the array equal NULL.
	ERR_WRONG_INDEX - the _index is not in the correct range (0 <= _index <=numOfItems-1) */
ADTErr VectorSet(Vector *_vector, size_t _index, int _item);

/*description- this function store the number of elements of Vector struct array in _numOfItems
input- _vector - structure pointer
	_numOfItems- pointer to store the number of elements in the array
output- ERR_OK
	ERR_NOT_INITIALIZED
errors- ERR_NOT_INITIALIZED - either the pointer or the array equal NULL. */
ADTErr VectorItemsNum(Vector *_vector, int* _numOfItems);

/*description- this function prints a struct of Vector
input- _vector - structure pointer
errors- in case the pointer is NULL nothing happens. */
void VectorPrint(Vector *_vector);







#endif /* __VECTOR_H__ */
