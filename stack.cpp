
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
    StackOverFlow = 1,
    NullDataPointer = 2,
    WrongDataType = 3,


};

//--------------------------------------------------------//

int StackPush   (struct Stack * stk, StackElements_t unit);         //----|
int StackPop    (struct Stack * stk);                               //    |
int StackCtor   (struct Stack * stk);                               //    |
int StackDtor   (struct Stack * stk);                               //    |----- Standart Stack Functions Stack
int StackDump   (struct Stack * stk);                               //    |
int StackCheck  (struct Stack * stk);                               //    |
void StackError (int ErrorCode);                                    //----|

int AddErrorInfo (int x, struct Stack * stk);
//int THOT (struct Stack * stk);                           //THOT - That Hash Over There


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

int StackCtor (struct Stack * stk)
{
    stk->Size = 0;
    stk->Capacity = 1;
    stk->Data = (StackElements_t *) calloc (stk->Capacity, sizeof(StackElements_t));

    stk->Size = 1;
    stk->Capacity = 0;
    StackCheck (stk);
    return 0;
}

//--------------------------------------------------------//

int StackPush (struct Stack * stk, StackElements_t unit)
{
    StackCheck (stk);

    stk->Data[stk->Size] = unit;
    printf ("element data[%lu] = %ld pushed\n", stk->Size, stk->Data[stk->Size]);
    stk->Size++;
    stk->Capacity = stk->Size * 2;
    stk->Data = (StackElements_t *) realloc (stk->Data, stk->Capacity*sizeof(StackElements_t));

    StackCheck (stk);
    return 0;
}

//--------------------------------------------------------//

int StackPop (struct Stack * stk)
{
    StackCheck (stk);

    printf ("The last element '%ld' is deleted\n", stk->Data[stk->Size-1]);
    stk->Data[stk->Size] = 0;
    stk->Size--;

    stk->Capacity = stk->Size * 2;
    stk->Data = (StackElements_t *) realloc (stk->Data, stk->Capacity*sizeof(StackElements_t));

    StackCheck (stk);
    return 0;
}

//--------------------------------------------------------//

int StackDtor (struct Stack * stk)
{
    StackCheck (stk);

    stk->Data = NULL;
    stk->Capacity = 0;
    stk->Size = 0;
    stk->ErrorCode = 0;

    StackCheck (stk);
    return 0;
}

//--------------------------------------------------------//

int StackCheck (struct Stack * stk)
{
    if (stk->Data == 0)
    {
        AddErrorInfo(NullDataPointer, stk);
    }
    else if (stk->Size > stk->Capacity)
    {
        AddErrorInfo(StackOverFlow, stk);
    }

    if (stk->ErrorCode)
    {    
        StackDump (stk);
        exit(1);
    }

    return 0;
}


//--------------------------------------------------------//

void StackError (int ErrorCode)
{
    switch (ErrorCode) {
        
        case StackOverFlow:
            printf ("Stack is overflowed\n");
            break;

        case NullDataPointer: 
            printf ("NULL pointer file\n");
            break;

        default:
            printf ("Unknown issue code:/ Code: %d\n", ErrorCode);
            break;
    }
}

//--------------------------------------------------------//

int StackDump (struct Stack * stk)
{
    printf ("\n\n");
    printf ("----------------------\n"
            "| Stack State Report |\n"
            "----------------------\n\n");

    printf ("----------------------\n");
    printf ("Stack data size: %lu\n", stk->Size);
    printf ("Stack capacity:  %lu\n", stk->Capacity);
    printf ("----------------------\n");
    
    if (stk->ErrorCode != 0)
    {
        printf ("We got some issues!\n\n");
        int CharAmount = 0;
        for (int i = 0; stk->ErrorCode != 0; i++)
        {
            int ten = (int) pow(10, i);
            CharAmount = i * (stk->ErrorCode % ten);
            if (CharAmount)
                StackError (CharAmount);
            stk->ErrorCode /= ten;
        }
    }

    return 0;
}

int AddErrorInfo (int x, struct Stack * stk)
{
    int ten = (int) pow(10, (double) x);
    stk->ErrorCode += ten;
    printf("%d", stk->ErrorCode);

    return 0;
}
