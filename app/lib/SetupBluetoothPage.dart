import 'dart:async';
import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';



class SetupBluetoothPage extends StatefulWidget {
  const SetupBluetoothPage({Key? key}) : super(key: key);

  @override
  State<SetupBluetoothPage> createState() => _SetupBluetoothPage();
}

class _SetupBluetoothPage extends State<SetupBluetoothPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('Setup Bluetooth'),
        backgroundColor: Colors.teal,
      ),
      
      );
  }
}

class Communication {
  connectBl(String address) {}
  
  void sendMessage(String s) {}
}