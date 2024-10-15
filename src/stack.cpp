#include "../headers/stack.h"

//--------------------------------------------------------//

int main ()
{
    Stack stk = {};
//    sample code
    StackCtor (&stk);
    StackPush (&stk, 10);
    StackPush (&stk, 20);
    StackPush (&stk, 30);
    StackPush (&stk, 40);
    StackPush (&stk, 50);
    StackSqrt (&stk);
    StackPush (&stk, 60);
    StackPop  (&stk);
    StackPush (&stk, 70);
    StackDump (&stk);
}
