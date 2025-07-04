import 'package:ffs_example/base_test.dart';
import 'package:flutter/material.dart';

void main(List<String> args) {
  baseTest();
  nativeDartPortTest();
  nativeCallableTest();

  runApp(MyApp());
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        body: Center(
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            spacing: 10,
            children: [
              Text('Hello'),
              ElevatedButton(onPressed: () {}, child: Text("Button")),
            ],
          ),
        ),
      ),
    );
  }
}
