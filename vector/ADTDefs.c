#include "ADTDefs.h"

const char* ErrDescription[] = 
{
	"OK",
	"General Errror",
	"Initialization error",
	"Allocation error",
	"ReAllocation error",
	"Unerflow error",
	"Overflow error",
	"Worng index",
	"No items in the array"
};

void HandleErr(ADTErr errNum, char* msg)
{
	if(errNum)
	{
		printf("ErrNum=%d, ErrDescription=%s, msg=%s\n",
		errNum, ErrDescription[errNum], msg);
	}
}



