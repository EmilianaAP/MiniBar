import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';

class AllDrinksPage extends StatefulWidget {
  const AllDrinksPage({Key? key}) : super(key: key);

  @override
  State<AllDrinksPage> createState() => _AllDrinksPageState();
}

class _AllDrinksPageState extends State<AllDrinksPage> {
  final ScrollController _controllerOne = ScrollController();
  final List<String> _items = [];
  final TextEditingController _textEditingController = TextEditingController();

  @override
  void initState() {
    super.initState();
    _loadItems();
  }

  Future<void> _loadItems() async {
    //SharedPreferences.setMockInitialValues({});
    final prefs = await SharedPreferences.getInstance();
    final itemsJson = prefs.getString('items');
    if (itemsJson != null) {
      final items = jsonDecode(itemsJson) as List<dynamic>;
      setState(() {
        _items.addAll(items.cast<String>());
      });
    }
  }


  Future<void> _saveItems() async {
    final prefs = await SharedPreferences.getInstance();
    await prefs.setString('items', jsonEncode(_items));
    print('itemsJson: $prefs');
  }

  void _addItemToList() {
    setState(() {
      _items.add(_textEditingController.text);
      _textEditingController.clear();
      _saveItems();
    });
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('All Drinks'),
        backgroundColor: Colors.teal,
      ),
      body: Column(
        children: [
          Expanded(
            child: Scrollbar(
              controller: _controllerOne,
              thumbVisibility: true,
              child: Padding(
                padding: const EdgeInsets.all(8.0),
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
                          style: const TextStyle(
                            color: Colors.white,
                            fontSize: 18.0,
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
                          fixedSize:
                              MaterialStateProperty.all<Size>(const Size(200.0, 60.0)),
                        ),
                      ),
                    );
                  },
                ),
              ),
            ),
          ),
          Padding(
            padding: const EdgeInsets.symmetric(horizontal: 8.0),
            child: Row(
              children: [
                Expanded(
                  child: TextField(
                    controller: _textEditingController,
                    decoration: const InputDecoration(
                      hintText: 'Add a new item',
                    ),
                  ),
                ),
                const SizedBox(width: 8.0),
                ElevatedButton(
                  onPressed: _addItemToList,
                  child: const Text('Add'),
                  style: ButtonStyle(
                    backgroundColor:
                        MaterialStateProperty.all<Color>(Colors.teal),
                    shape: MaterialStateProperty.all<RoundedRectangleBorder>(
                      RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(10.0),
                      ),
                    ),
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }
}
