#pragma once

#include "../include/dart_api.h"

typedef void (*PrintDebugCallbackType)(const char *str);

void registerPrintDebugCallback(PrintDebugCallbackType fun);

void printDebug(const char *format, ...);
