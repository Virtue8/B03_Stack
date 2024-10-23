#ifndef STACK_H
#define STACK_H

//--------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

#define COLORED_LINE(COLOR, ...) \
printf ("%s", COLOR);\
printf (__VA_ARGS__);\
printf ("%s", RESET)

typedef long int StackElem_t;
const StackElem_t CANARY_VALUE = 0xC0110CF00;

//--------------------------------------------------------//

struct Stack
{
    StackElem_t LeftCanary  = CANARY_VALUE;

    StackElem_t * Data      = NULL;
    size_t Size             = 0;
    size_t Capacity         = 0;

    int ErrorCode           = 0;
    
    StackElem_t RightCanary = CANARY_VALUE;
};

enum ErrorCodes {
    OK                      = 0,
    ERR                     = 1,
    NULL_STRUCT_POINTER     = 2,
    NULL_DATA_POINTER       = 3,
    STACK_OVERFLOW          = 4,
    LEFT_CANARY_DEATH       = 5,
    RIGHT_CANARY_DEATH      = 6,
    SIZE_ERR                = 7,
    CAPACITY_ERR            = 8,
    FILE_ERR                = 9,
    REALLOC_ERR             = 10,
};

const double EPSILON = pow (10, -6);

//--------------------------------------------------------//

StackElem_t StackPush   (struct Stack * stk, StackElem_t unit);
StackElem_t StackPop    (struct Stack * stk);

StackElem_t StackAdd    (struct Stack * stk);
StackElem_t StackSub    (struct Stack * stk);
StackElem_t StackMul    (struct Stack * stk);
StackElem_t StackDiv    (struct Stack * stk);
StackElem_t StackSqrt   (struct Stack * stk);
StackElem_t StackSin    (struct Stack * stk);
StackElem_t StackCos    (struct Stack * stk);

void StackCtor   (struct Stack * stk);
void StackDtor   (struct Stack * stk);

int StackDump   (struct Stack * stk);
int StackCheck  (struct Stack * stk);
void StackError (int ErrorCode, Stack * stk);

bool CompareTwo (double k1, double k2);
void MemDump (struct Stack * stk);

#endif