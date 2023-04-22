import 'package:flutter/material.dart';
import 'SetupBluetoothPage.dart';
import 'SetupDrinksPage.dart';

class SetupPage extends StatelessWidget {
  const SetupPage({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text('Setup'),
        backgroundColor: Colors.teal, 
      ),
      body: Center(
        child: Column(
          mainAxisAlignment: MainAxisAlignment.center,
          children: <Widget>[
            ElevatedButton(
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => SetupBluetoothPage()),
                );
              },
              child: Text(
                'BLAH',
                style: TextStyle(
                  color: Colors.white,
                  fontSize: 22.0,
                ),
              ),
              style: ButtonStyle(
                backgroundColor:
                    MaterialStateProperty.all<Color>(Colors.teal),
                shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                  RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(10.0),
                  ),
                ),
                fixedSize: MaterialStateProperty.all<Size>(Size(300.0, 75.0)),
              ),
            ),
            SizedBox(height: 20.0),
            ElevatedButton(
              onPressed: () {
                Navigator.push(
                  context,
                  MaterialPageRoute(builder: (context) => SetupDrinksPage()),
                );
              },
              child: Text(
                'Setup Drinks',
                style: TextStyle(
                  color: Colors.white,
                  fontSize: 22.0,
                ),
              ),
              style: ButtonStyle(
                backgroundColor:
                    MaterialStateProperty.all<Color>(Colors.teal),
                shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                  RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(10.0),
                  ),
                ),
                fixedSize: MaterialStateProperty.all<Size>(Size(300.0, 75.0)),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
