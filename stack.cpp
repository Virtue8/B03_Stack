
//--------------------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#define LEGITCHECK (if (err!=0) err =)

//--------------------------------------------------------//

typedef double StackElements_t;

struct Stack
{
    StackElements_t * Data = NULL;
    size_t Size = 0;
    size_t Capacity = 0;
    //error type error; (TODO: enam with types of errors);

};

//--------------------------------------------------------//

int StackPush   (struct Stack * stk, StackElements_t unit);
int StackPop    (struct Stack * stk);
int StackCtor   (struct Stack * stk, size_t cap);
//int StackDtor   ();
//int StackDump   ();
//int StackOK     ();
//int StackError  ();


//--------------------------------------------------------//

int main ()
{
    int err = 0;
    Stack stk = {};

    if (err!=0) err = StackCtor (&stk, 10);
    if (err!=0) err = StackPush (&stk, 10);
    if (err!=0) err = StackPush (&stk, 20);
    if (err!=0) err = StackPush (&stk, 30);
    if (err!=0) err = StackPush (&stk, 40);
    if (err!=0) err = StackPush (&stk, 50);
}

//--------------------------------------------------------//

int StackCtor (struct Stack * stk, size_t cap)     //return error type;
{
    //verification       switch(if) zero stack                          ewh
    stk->Size = 0;
    stk->Capacity = cap;           //TODO: calloc(data size);
    stk->Data[cap] = {};
    //verification
    return 1;
}

//--------------------------------------------------------//

int StackPush (struct Stack * stk, StackElements_t unit)
{                                                //stack increase
    stk->Data[stk->Size - 1] = unit;
    stk->Size++;

    return 1;
}

//--------------------------------------------------------//

int StackPop (struct Stack * stk)
{                                       //maybe return stack_element, but as for me error type the same
    stk->Data[stk->Size - 1] = 0;       //stack decrease
    stk->Size--;                        //last pop elemen in structure stack

    return 1;
}

//--------------------------------------------------------//