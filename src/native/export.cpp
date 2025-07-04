#include "export.h"
#include "common.h"
#include <iostream>
#include <thread>
#include <cstring>
#include <cstdlib>

#include "../include/dart_api_dl.h"

int add(int a, int b) 
{
    printWithFlush("c: call add(%d, %d)", a, b);
    return a + b;
}

/////////////////////////// NativeCallable Test ////////////////////////////////
void httpWork(char *uri, NativeHttpCallback callback)
{
    printf("c: httpWork start\n");
    fflush(stdout);
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    char response[] = "hello world";

    printf("c: httpWork call dart callback\n");
    fflush(stdout);
    callback(response);

    printf("c: httpWork done\n");
    fflush(stdout);
}

void nativeHttpGet(char *uri, NativeHttpCallback callback)
{
    printWithFlush("c: start httpWork\n");

    std::thread([callback]() {
        std::this_thread::sleep_for(std::chrono::seconds(3));


        char *response = (char *)malloc(100);
        snprintf(response, 100, "Hello World %d", 123);

        printWithFlush("c: Get Response, Call onResponse %p\n", response);

        callback(response);

        printWithFlush("c: onResponse done, bye");
    }).detach();
}

void nativeFree(void *ptr) {
    free(ptr);
}

/////////////////////////// Send Port Test /////////////////////////////////////
int InitDartApiDL(void *data)
{
    return Dart_InitializeApiDL(data);
}

Dart_Port send_port_;
Dart_Port recv_port;
std::thread *send_thread = nullptr;

void messageHandler(Dart_Port port, Dart_CObject* message)
{
    printf("printf: C: Receiving message from Dart.\n");
    fflush(stdout);

    std::string type_str = "C: Receiving message from Dart.";
    type_str += " type = " + std::to_string(message->type);
    type_str += ", value = " + std::to_string(message->value.as_int32);

    Dart_CObject dart_object;
    dart_object.type = Dart_CObject_kString;
    dart_object.value.as_string = type_str.c_str();
    Dart_PostCObject_DL(send_port_, &dart_object);
}

void work(void)
{

    recv_port = Dart_NewNativePort_DL("recv", messageHandler, true);
    if (recv_port == ILLEGAL_PORT) {
        printf("C   :  Creating recv port failed.");
    }

    Dart_CObject dart_object;
    dart_object.type = Dart_CObject_kSendPort;
    dart_object.value.as_int64 = recv_port;
    Dart_PostCObject_DL(send_port_, &dart_object);

    int index = 0;
    while (true)
    {
        Dart_CObject dart_object;
        dart_object.type = Dart_CObject_kInt64;
        dart_object.value.as_int64 = index;

        const bool result = Dart_PostCObject_DL(send_port_, &dart_object);
        if (!result)
            printf("C   :  Posting message to port failed.");

        index ++;

        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }
}

void nativeDartPortTestStartWork(Dart_Port port)
{
    send_port_ = port;
    send_thread = new std::thread(work);
}
