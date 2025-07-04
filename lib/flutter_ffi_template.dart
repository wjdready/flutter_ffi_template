// ignore_for_file: avoid_print

import 'bindings.dart';
import 'dart:ffi';
import 'dart:io';

export 'bindings.dart';

const String _libName = 'flutter_ffi_template';

final DynamicLibrary dylib = () {
  if (Platform.isMacOS || Platform.isIOS) {
    return DynamicLibrary.open('$_libName.framework/$_libName');
  }
  if (Platform.isAndroid || Platform.isLinux) {
    return DynamicLibrary.open('lib$_libName.so');
  }
  if (Platform.isWindows) {
    return DynamicLibrary.open('$_libName.dll');
  }
  throw UnsupportedError('Unknown platform: ${Platform.operatingSystem}');
}();

final flutter_ffi_template bindings = flutter_ffi_template(dylib);

int add(int a, int b) {
  return bindings.add(a, b);
}
