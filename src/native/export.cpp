#include "export.h"
#include "common.h"

int add(int a, int b) 
{
    printDebug("c: call add(%d, %d)", a, b);
    return a + b;
}
