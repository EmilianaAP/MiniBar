import 'package:flutter/material.dart';

class AvailableDrinksPage extends StatelessWidget {
  const AvailableDrinksPage({Key? key}) : super(key: key);
  
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Available Drinks'),
        backgroundColor: Colors.teal,
      ),

      body: Center(
        child: const MyStatefulWidget(),
      ),
    );
  }
}

class MyStatefulWidget extends StatefulWidget {
  const MyStatefulWidget({Key? key}) : super(key: key);

  @override
  State<MyStatefulWidget> createState() => _MyStatefulWidgetState();
}

class _MyStatefulWidgetState extends State<MyStatefulWidget> {
  final ScrollController _controllerOne = ScrollController();

  final List<String> _items = [
    'Apple',
    'Orange',
    'Peach',
    'Raspberry',
    'Apple & Orange',
    'Apple & Peach',
    'Apple & Raspberry',
    'Orange & Peach',
    'Orange & Raspberry',
    'Peach & Raspberry',
    'Apple & Orange & Peach',
    'Apple & Orange & Raspberry',
    'Apple & Peach & Raspberry',
    'Orange & Peach & Raspberry',
    'Apple & Orange & Peach & Raspberry',
  ];

  @override
  Widget build(BuildContext context) {
    return Scrollbar(
      controller: _controllerOne,
      thumbVisibility: true,
      child: Center(
        child: GridView.builder(
          controller: _controllerOne,
          itemCount: _items.length,
          gridDelegate: const SliverGridDelegateWithFixedCrossAxisCount(
            crossAxisCount: 1,
            childAspectRatio: 4,
          ),
        itemBuilder: (BuildContext context, int index) {
          return Center(
            child: ElevatedButton(
              onPressed: () {
                
              },
              child: Text(
                _items[index],
                style: TextStyle(
                  color: Colors.white,
                  fontSize: 18.0,
                ),
              ),
              style: ButtonStyle(
                backgroundColor: MaterialStateProperty.all<Color>(Colors.teal),
                shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                  RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(10.0),
                  ),
                ),
                fixedSize: MaterialStateProperty.all<Size>(Size(200.0, 60.0)),
              ),
            ),
          );
        },
      ),
    ),
    );
  }
}

class Communication {
  connectBl(String address) {}
  
  void sendMessage(String s) {}
}