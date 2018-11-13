#include "vector.h"
// You might need other includes for printing or whatnot


/* Take an already existing Vector as a parameter. Do not create a Vector
 inside this function. Set its internal memory size to match the value given in
 the parameter, allocate an appropriately-sized C array to hold the actual data,
 and initialize the size variable to 0. */

void init(Vector *vector, int memorySize)
{
    vector->array = (int *)malloc(memorySize * sizeof(int));
    vector->memorySize = memorySize;
    vector->size = 0;
}
