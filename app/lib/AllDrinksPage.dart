import 'package:flutter/material.dart';

class AllDrinksPage extends StatelessWidget {
  const AllDrinksPage({Key? key}) : super(key: key);
  
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('All Drinks'),
        backgroundColor: Colors.teal,
      ),

      body: Padding(
        padding: const EdgeInsets.all(8.0),
        child: const MyStatefulWidget(),
      ),

      floatingActionButton: FloatingActionButton(
        onPressed: () {
          // handle button press
        },
        child: const Icon(Icons.add, size: 32),
        backgroundColor: Colors.teal,
        elevation: 6,
      ),
      floatingActionButtonLocation: FloatingActionButtonLocation.centerFloat,
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
    'Lemonade',
    'Mojito',
    'Martini',
    'Daiquiri',
    'Margarita',
    'Gin and Tonic',
    'Cosmopolitan',
    'Bloody Mary',
    'Tequila Sunrise',
    'Sex on the Beach',
    'Zombie',
    'Blue Lagoon',
  ];

  @override
  Widget build(BuildContext context) {
    return Scrollbar(
      controller: _controllerOne,
      thumbVisibility: true,
      child: Padding(
        padding: const EdgeInsets.only(bottom: 80.0),
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
                // handle button press
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