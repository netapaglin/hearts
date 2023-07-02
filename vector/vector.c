#include <stdio.h>
#include<stdlib.h>
#include "ADTDefs.h"
#include "vector.h"
#define MAGIC_NUM 98765432
#define BLOCK_SIZE_FACTOR 2

struct Vector
{
	int* m_items;
	size_t m_originalSize; 
	size_t m_size;
	size_t m_nItems;
	size_t m_blockSize;
	int m_magicNum;
};


size_t GetVectorSize(Vector *_vector)
{
	return _vector -> m_size;
}

size_t GetVectorOriginalSize(Vector *_vector)
{
	return _vector -> m_originalSize;
}

size_t GetVectorNumItems(Vector *_vector)
{
	return _vector -> m_nItems;
}

size_t GetVectorBlockSize(Vector *_vector)
{
	return _vector -> m_blockSize;
}
/*
size_t GetVectorItems(Vector *_vector)
{
	return _vector -> m_items;
}*/

int GetVectorMagicNum(Vector *_vector)
{
	return _vector -> m_magicNum;
}






Vector* VectorCreate(size_t _initialSize, size_t _blockSize)
{
	Vector* arr;
	int* temp;
	if (_initialSize == 0 && _blockSize == 0)
	{
		return NULL;
	}
	arr = (Vector*)malloc( sizeof(Vector));
	 if(arr == NULL)
	 {
		 return NULL;
	 }
	  temp = (int*)malloc( _initialSize * sizeof(int));
	  if(temp == NULL)
	  {
	  		free(arr);
	    	return NULL;
	  }
	 arr->m_items = temp;
	 arr-> m_size = _initialSize ;
     arr-> m_originalSize = _initialSize ;
     arr-> m_blockSize = _blockSize;
     arr-> m_magicNum = MAGIC_NUM;
     arr->m_nItems = 0;
	 return arr ;
}

ADTErr VectorAdd(Vector *_vector, int _item)
{
	ADTErr resault;
    if(_vector == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if( (resault = CheakIncrease(_vector) ) != ERR_OK)
	{
		return resault;
	}
	_vector -> m_items[_vector -> m_nItems] = _item;
    _vector -> m_nItems += 1;
    return ERR_OK ;
}

int CheakIncrease(Vector *_vector)
{
	int *temp;
	int newSize;
	    if(_vector == NULL )
	   {
	  	 	return ERR_NOT_INITIALIZED;
	   }
	 	if (_vector -> m_nItems == _vector -> m_size)
	   {
	   		if (_vector ->m_blockSize == 0 )
	   		{
	   			return ERR_OVERFLOW;
	   		} 
	   		newSize =( _vector -> m_size + _vector ->m_blockSize) ;
	   		temp = (int*)realloc( _vector -> m_items ,newSize  * sizeof(int)); 
	   		if(temp == NULL)
			{
				return ERR_ALLOCATION_FAILED;
	 	    }
	 	    _vector -> m_size = newSize ; 	
	 	    _vector -> m_items = 	 temp;
	}	  
		 return ERR_OK;
}	

ADTErr VectorDelete(Vector *_vector, int* _item)
{
	int resault;
    if(_vector == NULL || _item == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_vector -> m_nItems  == 0)
	  {
	  		return ERR_UNDERFLOW;
	  }
if (_vector->m_blockSize != 0 &&
	_vector -> m_size > _vector -> m_originalSize  && 
	_vector -> m_size - _vector -> m_nItems >=  BLOCK_SIZE_FACTOR * _vector->m_blockSize)
	{
		if( (resault = CheakInDelete(_vector) ) != ERR_OK)
		{
			return resault;
		}
	}   
   * _item = _vector -> m_items[_vector -> m_nItems - 1];
   _vector ->  m_nItems --;
   return ERR_OK;
}

int CheakInDelete(Vector *_vector)
{
	int *temp = NULL;
	int newSize;
    if(_vector == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	 if(_vector ->  m_nItems  == 0 )
	{
		return ERR_UNDERFLOW;
	}
	newSize = _vector -> m_size - (_vector ->m_blockSize * BLOCK_SIZE_FACTOR)  ;
	temp = (int*)realloc( _vector -> m_items ,newSize  * sizeof(int)); 
	if(temp == NULL)
	 {
		return ERR_ALLOCATION_FAILED;
	 }
	  _vector -> m_size = newSize ; 
	 _vector->m_items = temp; 	
	 return ERR_OK;
}	

void VectorDestroy(Vector* _vector)
{
	if (_vector!= NULL && _vector-> m_magicNum != 0 )
	{
		free( _vector->m_items);
		free( _vector);
		 _vector-> m_magicNum = 0;
	}

}

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
    if(_vector == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	 if(_vector -> m_nItems == 0 || _index > _vector -> m_nItems - 1 || _index < 0)
	{
		return ERR_WRONG_INPUT;
	}
	
	*_item = _vector -> m_items[_index];
	return ERR_OK;
}


ADTErr VectorSet(Vector *_vector, size_t _index, int _item)
{
	 if(_vector == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
		 if(_vector -> m_nItems == 0 ||
		 _index > _vector -> m_nItems - 1 || 
		 _index < 0)
	{
		return ERR_WRONG_INPUT;
	}
	 _vector -> m_items[_index] = _item;
	return ERR_OK;
}

ADTErr VectorItemsNum(Vector *_vector, int* _numOfItems)
{
	 if(_vector == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	*_numOfItems =  _vector -> m_nItems;
	return ERR_OK;
}

void VectorPrint(Vector *_vector)
{
	int i;
	printf( " ***********************\n" );
	for ( i=0 ; i < _vector->m_nItems ; ++i)
   {
   	printf( " %d  , " , _vector->m_items[i]);
   	printf( " \n " );
   }
   printf( " ***********************\n" );
}


