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
      body: const Center(
        child: MyStatefulWidget(),
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
    'Lemonade',
    'Water',
    'Mojito',
    'Martini',
    'Daiquiri',
    'Margarita',
    'Manhattan',
    'Negroni',
    'Gin and Tonic',
    'Whiskey Sour',
    'Cosmopolitan',
    'Paloma',
    'Pina Colada',
    'Bloody Mary',
    'Tequila Sunrise',
    'Sex on the Beach',
    'Long Island Iced Tea',
    'Singapore Sling',
    'Zombie',
    'Blue Lagoon',
  ];

  @override
  Widget build(BuildContext context) {
    return Scrollbar(
      controller: _controllerOne,
      thumbVisibility: true,
      child: GridView.builder(
        controller: _controllerOne,
        itemCount: 20,
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
    );
  }
}