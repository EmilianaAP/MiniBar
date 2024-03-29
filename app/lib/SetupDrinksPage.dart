import 'package:flutter/material.dart';

class SetupDrinksPage extends StatefulWidget {
  const SetupDrinksPage({Key? key}) : super(key: key);

  @override
  State<SetupDrinksPage> createState() => _SetupDrinksPage();
}

class _SetupDrinksPage extends State<SetupDrinksPage> {
  String _selectedItem1 = 'Empty';
  String _selectedItem2 = 'Empty';
  String _selectedItem3 = 'Empty';
  String _selectedItem4 = 'Empty';
  List<String> _dropdownItems = ['Apple', 'Raspberry', 'Peach', 'Orange', 'Empty'];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Setup Drinks'),
        backgroundColor: Colors.teal,
      ),
      body: Column(
        mainAxisAlignment: MainAxisAlignment.center,
        children: [
          Center(
            child: DropdownButton<String>(
              value: _selectedItem1,
              onChanged: (String? newValue) {
                setState(() {
                  _selectedItem1 = newValue!;
                });
              },
              items: _dropdownItems.map((String value) {
                return DropdownMenuItem<String>(
                  value: value,
                  child: Text(value),
                );
              }).toList(),
              dropdownColor: Colors.white,
              style: TextStyle(
                fontSize: 24,
                color: Colors.black,
              ),
              elevation: 16,
              iconSize: 40,
              icon: Icon(Icons.arrow_downward),
              iconEnabledColor: Colors.black,
              isExpanded: true,
              underline: Container(
                height: 2,
                color: Colors.black,
              ),
            ),
          ),
          SizedBox(height: 16),

          Center(
            child: DropdownButton<String>(
              value: _selectedItem2,
              onChanged: (String? newValue) {
                setState(() {
                  _selectedItem2 = newValue!;
                });
              },
              items: _dropdownItems.map((String value) {
                return DropdownMenuItem<String>(
                  value: value,
                  child: Text(value),
                );
              }).toList(),
              dropdownColor: Colors.white,
              style: TextStyle(
                fontSize: 24,
                color: Colors.black,
              ),
              elevation: 16,
              iconSize: 40,
              icon: Icon(Icons.arrow_downward),
              iconEnabledColor: Colors.black,
              isExpanded: true,
              underline: Container(
                height: 2,
                color: Colors.black,
              ),
            ),
          ),
          SizedBox(height: 16),

          Center(
            child: DropdownButton<String>(
              value: _selectedItem3,
              onChanged: (String? newValue) {
                setState(() {
                  _selectedItem3 = newValue!;
                });
              },
              items: _dropdownItems.map((String value) {
                return DropdownMenuItem<String>(
                  value: value,
                  child: Text(value),
                );
              }).toList(),
              dropdownColor: Colors.white,
              style: TextStyle(
                fontSize: 24,
                color: Colors.black,
              ),
              elevation: 16,
              iconSize: 40,
              icon: Icon(Icons.arrow_downward),
              iconEnabledColor: Colors.black,
              isExpanded: true,
              underline: Container(
                height: 2,
                color: Colors.black,
              ),
            ),
          ),
          SizedBox(height: 16),

          Center(
            child: DropdownButton<String>(
              value: _selectedItem4,
              onChanged: (String? newValue) {
                setState(() {
                  _selectedItem4 = newValue!;
                });
              },
              items: _dropdownItems.map((String value) {
                return DropdownMenuItem<String>(
                  value: value,
                  child: Text(value),
                );
              }).toList(),
              dropdownColor: Colors.white,
              style: TextStyle(
                fontSize: 24,
                color: Colors.black,
              ),
              elevation: 16,
              iconSize: 40,
              icon: Icon(Icons.arrow_downward),
              iconEnabledColor: Colors.black,
              isExpanded: true,
              underline: Container(
                height: 2,
                color: Colors.black,
              ),
            ),
          ),
          SizedBox(height: 16),
        ],
      ),
    );
  }
}
