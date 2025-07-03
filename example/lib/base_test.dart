// ignore_for_file: avoid_print

import 'dart:ffi';

import 'package:ffi/ffi.dart';
import 'package:flutter_ffi_template/flutter_ffi_template.dart' as myffi;

void printDebug(Pointer<Char> format) {
  final msg = format.cast<Utf8>().toDartString();
  print(msg);
}

void baseTest() {
  final callback = Pointer.fromFunction<myffi.PrintDebugCallbackTypeFunction>(
    printDebug,
  );
  myffi.setPrintDebugCallback(callback);

  final c = myffi.add(5, 3);
  print(c);
}
