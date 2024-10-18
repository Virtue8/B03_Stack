#ifndef STACK_H
#define STACK_H

//--------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#include "StackFuncs.h"

typedef double StackElem_t;
const StackElem_t CANARY_VALUE = 0xC0110CF00;

//--------------------------------------------------------//

struct Stack
{
    StackElem_t LeftCanary  = CANARY_VALUE;

    StackElem_t * Data      = NULL;
    size_t Size             = 0;
    size_t Capacity         = 0;

    int ErrorCode           = 0;
    int Hash                = 0;
    
    StackElem_t RightCanary = CANARY_VALUE;
};

#endif