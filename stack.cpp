
//--------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#define LEGITCHECK if (err!=1) err =

//--------------------------------------------------------//

typedef long StackElements_t;

struct Stack
{
    StackElements_t * Data = NULL;
    size_t Size = 0;
    size_t Capacity = 0;

    int ErrorCode = 0;
};

enum ErrorCodes
{
    StackOverFlow,
    NullPointer,
};

//--------------------------------------------------------//

int StackPush   (struct Stack * stk, StackElements_t unit);         //----|
int StackPop    (struct Stack * stk);                               //    |
int StackCtor   (struct Stack * stk);                   //    |
int StackDtor   (struct Stack * stk);                               //    |----- Standart Stack Functions Stack
int StackDump   (struct Stack * stk);                               //    |
//int StackOK     ();                                               //    |
//int StackError  (struct Stack * stk);                             //----|


//--------------------------------------------------------//

int main ()
{
    int err = 0;
    Stack stk = {};

    LEGITCHECK StackCtor (&stk);
    LEGITCHECK StackPush (&stk, 10);
    LEGITCHECK StackPush (&stk, 20);
    LEGITCHECK StackPush (&stk, 30);
    LEGITCHECK StackPush (&stk, 40);
    LEGITCHECK StackPush (&stk, 50);
    LEGITCHECK StackPop  (&stk);
    LEGITCHECK StackPush (&stk, 60);
    LEGITCHECK StackPush (&stk, 70);
    LEGITCHECK StackDump (&stk);
}

//--------------------------------------------------------//

int StackCtor (struct Stack * stk)     //return error type;
{
    //verification                 switch(if) zero stack ewh
    stk->Size = 0;
    stk->Capacity = 1;
    stk->Data = (StackElements_t *) calloc (stk->Capacity, sizeof(StackElements_t));
    //verification
    return 0;
}

//--------------------------------------------------------//

int StackPush (struct Stack * stk, StackElements_t unit)
{
    stk->Data[stk->Size] = unit;
    printf ("element data[%lu] = %ld pushed\n", stk->Size, stk->Data[stk->Size]);
    stk->Size++;
    stk->Capacity = stk->Size * 2;
    stk->Data = (StackElements_t *) realloc (stk->Data, stk->Capacity*sizeof(StackElements_t));

    return 0;
}

//--------------------------------------------------------//

int StackPop (struct Stack * stk)
{
    printf ("The last element '%ld' is deleted\n", stk->Data[stk->Size-1]);

    stk->Data[stk->Size] = 0;
    stk->Size--;

    stk->Capacity = stk->Size * 2;
    stk->Data = (StackElements_t *) realloc (stk->Data, stk->Capacity*sizeof(StackElements_t));

    return 0;
}

//--------------------------------------------------------//

int StackDtor (struct Stack * stk)
{
    stk->Data = NULL;
    stk->Capacity = 0;
    stk->Size = 0;
    stk->ErrorCode = 0;

    return 0;
}

//--------------------------------------------------------//
/*
int StackError (struct Stack * stk)
{

}
*/
//--------------------------------------------------------//

int StackDump (struct Stack * stk)
{
    printf ("\n\n");
    printf ("----------------------\n"
            "| Stack State Report |\n"
            "----------------------\n\n");

    printf ("Error code: %d \n", stk->ErrorCode);
    printf ("----------------------\n");
    printf ("Stack data size: %lu\n", stk->Size);
    printf ("Stack capacity:  %lu\n", stk->Capacity);
    printf ("----------------------\n");

    return 0;
}
