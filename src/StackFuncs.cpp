#ifndef STACKFUNCS_CPP
#define STACKFUNCS_CPP

#include "../headers/StackFuncs.h"

/*
StackElem_t StackOut    (struct Stack * stk)
StackElem_t StackIn     (struct Stack * stk)
*/

//--------------------------------------------------------//

StackElem_t StackAdd (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    StackElem_t b = StackPop (stk);
    return StackPush (stk, b + a);
    
    StackCheck (stk);
}

//--------------------------------------------------------//

StackElem_t StackSub (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    StackElem_t b = StackPop (stk);
    return StackPush (stk, b - a);
}

//--------------------------------------------------------//

StackElem_t StackMul (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    StackElem_t b = StackPop (stk);
    return StackPush (stk, b * a);
}

//--------------------------------------------------------//

StackElem_t StackDiv (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    StackElem_t b = StackPop (stk);
    return StackPush (stk, b / a);
}

//--------------------------------------------------------//

StackElem_t StackSqrt (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    return StackPush (stk, sqrt (a));;
}

//--------------------------------------------------------//

StackElem_t StackSin (struct Stack * stk)
{
    StackCheck (stk);
    
    StackElem_t a = StackPop (stk);
    return StackPush (stk, sin (a));
}

//--------------------------------------------------------//

StackElem_t StackCos (struct Stack * stk)
{
    StackCheck (stk);

    StackElem_t a = StackPop (stk);
    return StackPush (stk, cos (a));
}

//--------------------------------------------------------//

void StackCtor (struct Stack * stk)
{
    stk->Size = 0;
    stk->Capacity = 1;
    stk->Data = (StackElem_t *) calloc (stk->Capacity, sizeof(StackElem_t));
    /**(stk->Data) = CanaryValue;
    stk->Data += sizeof (StackElem_t);
    *(stk->Data + stk->Capacity * sizeof (StackElem_t)) = CanaryValue;

    StackCheck (stk);*/
}

//--------------------------------------------------------//

StackElem_t StackPush (struct Stack * stk, StackElem_t unit)
{
    StackCheck (stk);

    stk->Data[stk->Size] = unit;
    stk->Size++;
    stk->Capacity = stk->Size * 2;
    stk->Data = (StackElem_t *) realloc (stk->Data, (stk->Capacity)*sizeof(StackElem_t));
    /**(stk->Data) = CanaryValue;
    stk->Data += sizeof (StackElem_t);
    *(stk->Data + stk->Capacity * sizeof (StackElem_t)) = CanaryValue;*/



    StackCheck (stk);
    return unit;
}

//--------------------------------------------------------//

StackElem_t StackPop (struct Stack * stk)
{
    StackCheck (stk);

    stk->Data[stk->Size] = 0;
    stk->Size--;

    stk->Capacity = stk->Size * 2;
    stk->Data = (StackElem_t *) realloc (stk->Data, stk->Capacity*sizeof(StackElem_t));

    StackCheck (stk);
    return stk->Data[stk->Size];
}

//--------------------------------------------------------//

void StackDtor (struct Stack * stk)
{
    StackCheck (stk);

    free(stk->Data);
    stk->Data = NULL;
    stk->Capacity = 0;
    stk->Size = 0;
    stk->ErrorCode = 0;

    StackCheck (stk);
}

//--------------------------------------------------------//

int StackCheck (struct Stack * stk)
{
    if (stk->Data == 0)
    {
        AddErrorInfo(NULL_DATA_POINTER, stk);
    }
    else if (stk->Size > stk->Capacity)
    {
        AddErrorInfo(STACK_OVERFLOW, stk);
    }

    if (stk->ErrorCode)
    {    
        StackDump (stk);
        exit (1);
    }

    return 0;
}


//--------------------------------------------------------//

void StackError (int ErrorCode)
{
    switch (ErrorCode) {
        
        case STACK_OVERFLOW:
            COLORED_LINE (RED, "Stack is overflowed\n");
            break;

        case NULL_DATA_POINTER: 
            COLORED_LINE (RED, "NULL pointer file\n");
            break;

        default:
            COLORED_LINE (RED, "Unknown issue code:/ Code: %d\n", ErrorCode);
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
    printf ("| Data Size:    %lu\n", stk->Size);
    printf ("| Capacity:     %lu\n", stk->Capacity);
    printf ("----------------------\n\n");

    printf ("Stack Data:    ");
    for (size_t i = 0; i < stk->Size; i++)
        printf ("%.2f    ", stk->Data[i]);
    printf ("\n\n");
    
    if (stk->ErrorCode != 0)
    {
        COLORED_LINE (RED, "\nWe got some issues!\n");
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

#endif