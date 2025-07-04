// ignore_for_file: avoid_print

import 'dart:async';
import 'dart:ffi';
import 'dart:isolate';

import 'package:ffi/ffi.dart';
import 'package:flutter_ffi_template/flutter_ffi_template.dart' as myffi;

void printDebug(Pointer<Char> format) {
  final msg = format.cast<Utf8>().toDartString();
  print(msg);
}

void baseTest() {
  print("start InitDartApiDL");
  final res = myffi.bindings.InitDartApiDL(NativeApi.initializeApiDLData);
  print("InitDartApiDL res = $res");

  // final c = myffi.add(5, 3);
  // print(c);
}

/////////////////////////////// DartPort Test //////////////////////////////////
void nativeDartPortTest()
{
  SendPort? nativeSendPort;

  final ReceivePort receivePort = ReceivePort()..listen((message) {
    if (message is SendPort) {
      print("dart: get send port from c");
      nativeSendPort = message;
    }
    print("dart: receive message from c: $message");
  });
  myffi.bindings.nativeDartPortTestStartWork(receivePort.sendPort.nativePort);

  Timer.periodic(Duration(seconds: 1), (timer) {
    if (nativeSendPort != null) {
      nativeSendPort?.send(timer.tick);
    }
  });
}

/////////////////////////////// NativeCallable Test ////////////////////////////
// Processes a simple HTTP GET request using a native HTTP library that
// processes the request on a background thread.
Future<String> httpGet(String uri) async {
  final uriPointer = uri.toNativeUtf8();

  // Create the NativeCallable.listener.
  final completer = Completer<String>();
  late final NativeCallable<myffi.NativeHttpCallbackFunction> callback;
  void onResponse(Pointer<Char> responsePointer) {

    print("Dart: onResponse $responsePointer");

    completer.complete(responsePointer.cast<Utf8>().toDartString());
    
    print("Dart: onResponse free");

    // calloc.free(responsePointer);
    myffi.bindings.nativeFree(responsePointer.cast());

    calloc.free(uriPointer);

    print("Dart: onResponse free done");

    // Remember to close the NativeCallable once the native API is
    // finished with it, otherwise this isolate will stay alive
    // indefinitely.
    callback.close();
    print("Dart: onResponse done, callback close");
  }

  callback = NativeCallable.listener(onResponse);

  // Invoke the native HTTP API. Our example HTTP library processes our
  // request on a background thread, and calls the callback on that same
  // thread when it receives the response.
  myffi.bindings.nativeHttpGet(uriPointer.cast(), callback.nativeFunction);
  print("Dart: waiting response");
  return completer.future;
}

void nativeCallableTest() async {

  while(true) {
    final response = await httpGet("http://www.google.com");
    print("response = $response");
    await Future.delayed(Duration(seconds: 3));
  }
}
