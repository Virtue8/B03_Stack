
//--------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#define LEGITCHECK if (err!=0) err =

//--------------------------------------------------------//

typedef double StackElements_t;

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
int StackCtor   (struct Stack * stk, size_t cap);                   //    |
int StackDtor   ();                                                 //    |----- Standart Stack Functions Stack
int StackDump   (struct Stack * stk);                               //    |
int StackOK     ();                                                 //    |
int StackError  (struct Stack * stk);                               //----|


//--------------------------------------------------------//

int main ()
{
    int err = 0;
    Stack stk = {};

    LEGITCHECK StackCtor (&stk, 10);
    LEGITCHECK StackPush (&stk, 10);
    LEGITCHECK StackPush (&stk, 20);
    LEGITCHECK StackPush (&stk, 30);
    LEGITCHECK StackPush (&stk, 40);
    LEGITCHECK StackPush (&stk, 50);
}

//--------------------------------------------------------//

int StackCtor (struct Stack * stk, size_t cap)     //return error type;
{
    //verification                 switch(if) zero stack ewh
    stk->Size = 0;
    stk->Capacity = cap;
    stk->Data = (StackElements_t *) calloc (stk->Capacity, sizeof(StackElements_t));
    //verification
    return 1;
}

//--------------------------------------------------------//

int StackPush (struct Stack * stk, StackElements_t unit)
{
    stk->Capacity = stk->Size*2;
    stk->Data = (StackElements_t *) realloc (stk->Data, stk->Capacity);
    stk->Data[stk->Size - 1] = unit;

    return 1;
}

//--------------------------------------------------------//

int StackPop (struct Stack * stk)
{
    stk->Capacity = stk->Size*2;
    stk->Data = (StackElements_t *) realloc (stk->Data, stk->Capacity);
    stk->Data[stk->Size - 1] = 0;

    return 1;
}

//--------------------------------------------------------//

int StackDtor (struct Stack * stk)
{
    stk->Data = NULL;
    stk->Capacity = 0;
    stk->Size = 0;
    stk->ErrorCode = 0;

    return 1;
}

//--------------------------------------------------------//

int StackError (struct Stack * stk)
{

}

//--------------------------------------------------------//

int StackDump (struct Stack * stk)
{
    printf ("----------------------\n"
            "| Stack State Report |\n"
            "----------------------\n\n");

    printf ("Error code %d: s", stk->ErrorCode);
    printf ("----------------------\n");
    printf ("Stack data size: %d\n", stk->Size);
    printf ("Stack capacity:  %d\n", stk->Capacity);
    printf ("----------------------\n");
}
