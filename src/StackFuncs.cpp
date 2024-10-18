#ifndef STACKFUNCS_CPP
#define STACKFUNCS_CPP

#include "../headers/StackFuncs.h"

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
    stk->Data = (StackElem_t *) calloc (stk->Capacity + 2, sizeof(StackElem_t));
    *(stk->Data) = CANARY_VALUE;
    stk->Data += 1;
    *(stk->Data + stk->Capacity) = CANARY_VALUE;

    stk->LeftCanary = CANARY_VALUE;
    stk->RightCanary = CANARY_VALUE;
    stk->Hash = 4;

    StackCheck (stk);
}

//--------------------------------------------------------//

StackElem_t StackPush (struct Stack * stk, StackElem_t unit)
{
    if (stk->Capacity != 1)
        StackCheck (stk);

    stk->Data[stk->Size] = unit;
    stk->Size++;
    
    StackElem_t * temp_data = (StackElem_t *) realloc (stk->Data, 2 * (stk->Capacity + 1));

    if (temp_data == NULL) 
        stk->ErrorCode = REALLOC_ERR;

    stk->Data = temp_data;
    stk->Data += 1;

    *(stk->Data + stk->Capacity) = 0;
    stk->Capacity = stk->Size * 2;
    *(stk->Data + stk->Capacity) = CANARY_VALUE;

    StackCheck (stk);
    return unit;
}

//--------------------------------------------------------//

StackElem_t StackPop (struct Stack * stk)
{
    StackCheck (stk);

    stk->Data[stk->Size] = 0;
    stk->Size--;

    StackElem_t * temp_data = (StackElem_t *) realloc (stk->Data, 2 * (stk->Capacity + 1));

    if (temp_data == NULL) 
        stk->ErrorCode = REALLOC_ERR;

    stk->Data = temp_data;
    stk->Data += 1;

    *(stk->Data + stk->Capacity) = 0;
    stk->Capacity = stk->Size / 2;
    *(stk->Data + stk->Capacity) = CANARY_VALUE;

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
    DaSickHash (stk->Data, stk->Size);

    if (&stk == NULL)
        stk->ErrorCode = NULL_STRUCT_POINTER;
    else if ((stk->Data == NULL))
        stk->ErrorCode = NULL_DATA_POINTER;
    else if (stk->Size > stk->Capacity)
        stk->ErrorCode = STACK_OVERFLOW;
    else if (!CompareTwo(stk->Hash, 4))
        stk->ErrorCode = HASH_ERR;
    else if (!CompareTwo(*(stk->Data - 1), CANARY_VALUE))
        stk->ErrorCode = LEFT_CANARY_DEATH;
    else if (!CompareTwo(*(stk->Data + stk->Capacity ), CANARY_VALUE))
        stk->ErrorCode = RIGHT_CANARY_DEATH;
    else if (!isfinite(stk->Size))
        stk->ErrorCode = SIZE_ERR;
    else if (!isfinite(stk->Capacity))
        stk->ErrorCode = CAPACITY_ERR;

    if (stk->ErrorCode)
    {    
        StackDump (stk);
        exit (1);
    }

    return 0;
}


//--------------------------------------------------------//

void StackError (int ErrorCode, Stack * stk)
{
    switch (ErrorCode) {
        
        case STACK_OVERFLOW:
            COLORED_LINE (RED, "Stack is overflowed\n");
            break;

        case NULL_DATA_POINTER: 
            COLORED_LINE (RED, "NULL pointer file\n");
            break;

        case NULL_STRUCT_POINTER: 
            COLORED_LINE (RED, "NULL struct pointer\n");
            break;

        case HASH_ERR: 
            COLORED_LINE (RED, "Hash doesn't match the required value\n");
            COLORED_LINE (RED, "UNAUTHORISED ACCESS TO DATA (or you're just dumb)\n");
            break;

        case LEFT_CANARY_DEATH: 
            COLORED_LINE (RED, "Data destruction from left side\n");
            break;

        case RIGHT_CANARY_DEATH: 
            COLORED_LINE (RED, "Data destruction from right side\n");
            break;

        case SIZE_ERR: 
            COLORED_LINE (RED, "Size error\n");
            printf ("%ld\n", stk->Size);
            break;

        case CAPACITY_ERR: 
            COLORED_LINE (RED, "Capacity error\n");
            printf ("%ld\n", stk->Capacity);
            break;

        case REALLOC_ERR: 
            COLORED_LINE (RED, "Reallocation error\n");
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

    printf ("%f\n", *(stk->Data - sizeof (StackElem_t)));

    printf ("Stack Data:    ");
    for (size_t i = 0; i < stk->Size; i++)
        printf ("%.2f    ", stk->Data[i]);
    printf ("\n\n");
    
    if (stk->ErrorCode != 0)
    {
        COLORED_LINE (RED, "\nWe got some issues!\n");
        StackError (stk->ErrorCode, stk);
    }

    return 0;
}

static unsigned long DaSickHash(const void* str, size_t Size)
{
    const unsigned char* p = (const unsigned char*) str;
    unsigned long hash = 5381;
    unsigned long c = 0;

    for (size_t i = 0; i < Size; i++)
    {
        c = * (p + i);
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

bool CompareTwo (double k1, double k2)
{
    return (fabs (k1 - k2) <= EPSILON);
}

#endif