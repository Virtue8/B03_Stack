#ifndef STACKFUNCS_H
#define STACKFUNCS_H
#include "stack.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

#define COLORED_LINE(COLOR, ...) \
printf ("%s", COLOR);\
printf (__VA_ARGS__);\
printf ("%s", RESET)


enum ErrorCodes {
    OK                      = 0,
    ERR                     = 1,
    NULL_STRUCT_POINTER     = 2,
    NULL_DATA_POINTER       = 3,
    STACK_OVERFLOW          = 4,
    HASH_ERR                = 5,
    LEFT_CANARY_DEATH       = 6,
    RIGHT_CANARY_DEATH      = 7,
    SIZE_ERR                = 8,
    CAPACITY_ERR            = 9,
    FILE_ERR                = 10,
    REALLOC_ERR             = 11,
};

typedef double StackElem_t;
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
static unsigned long DaSickHash(const void* str, size_t size);

#endif