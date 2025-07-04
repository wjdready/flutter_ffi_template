#pragma once

#include "../include/dart_api.h"

typedef void (*nativeCallableTestCallbackType)(int x, int *ret);
typedef void (*NativeHttpCallback)(const char * resp);

int add(int a, int b);

/////////////////////////// Send Port Test /////////////////////////////////////
int InitDartApiDL(void *data);
void nativeDartPortTestStartWork(Dart_Port port);
void nativeCallableTest(int x, nativeCallableTestCallbackType callback);

/////////////////////////// NativeCallable Test ////////////////////////////////
void nativeHttpGet(char *uri, NativeHttpCallback callback);
void nativeFree(void *ptr);
