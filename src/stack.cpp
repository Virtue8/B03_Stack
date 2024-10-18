#include "../headers/stack.h"

//--------------------------------------------------------//

int main ()
{
    Stack stk = {};
//    sample code
    printf ("yeeeeeeeeeee\n");
    StackCtor (&stk);
    printf ("yeeeeeeeeeee\n");
    StackPush (&stk, 10);
    printf ("yeeeeeeeeeee\n");
    StackPush (&stk, 20);
    StackPush (&stk, 30);
    StackPush (&stk, 40);
    StackPush (&stk, 50);
    printf ("yeeeeeeeeeee\n");
    StackSqrt (&stk);
    StackPush (&stk, 60);
    StackPop  (&stk);
    StackPush (&stk, 70);
    StackDump (&stk);
}
