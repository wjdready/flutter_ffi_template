#include "common.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

static PrintDebugCallbackType printDebugCallback;

void printDebug(const char *format, ...)
{
    if (printDebugCallback == NULL)
        return;

    va_list args;
    va_start(args, format);

    int n = vsnprintf(NULL, 0, format, args);
    char *buf = (char *)malloc(n + 1);
    if (buf == NULL)
        return;

    vsnprintf(buf, n + 1, format, args);

    va_end(args);
    printDebugCallback(buf);

    free(buf);
}

void registerPrintDebugCallback(PrintDebugCallbackType fun)
{
    printDebugCallback = fun;
}
