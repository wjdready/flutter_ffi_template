#pragma once

#include "../include/dart_api.h"

#define printWithFlush(...) { \
    printf(__VA_ARGS__); \
    fflush(stdout); \
}
