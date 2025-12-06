// A basic Dart test file to exercise tokenization and parsing.

import 'dart:math';
import 'package:http/http.dart' as http;

// Top-level variables
const double piValue = 3.14159;
var counter = 0;
final String greeting = "Hello Dart!";

// An enum for testing
enum Status { idle, running, failed }

// A simple class
class Person {
  final String name;
  int age;

  Person(this.name, this.age);

  void sayHello() {
    print("Hi, I'm $name and I'm $age years old.");
  }
}

// A function with optional + named parameters
int add(int a, [int b = 0, int c = 0]) {
  return a + b + c;
}

// Arrow function
double square(num x) => x * x;

// Async function test
Future<String> fetchData(String url) async {
  final response = await http.get(Uri.parse(url));
  return "Status: ${response.statusCode}";
}

// Main entry point
void main() {
  var john = Person("John Doe", 30);
  john.sayHello();

  print("Square of 5 = ${square(5)}");
  print("Add(1,2,3) = ${add(1, 2, 3)}");

  // List & map literals
  List<int> numbers = [1, 2, 3, 4, 5];
  Map<String, dynamic> data = {
    "name": "Alice",
    "age": 22,
    "active": true
  };

  for (var n in numbers) {
    counter += n;
  }

  print("Counter = $counter");

  // Multi-line string
  String multi = """
This is a multi-line
Dart string with interpolation: ${data['name']}
""";

  print(multi);

  // Conditional expressions
  var status = Status.running;
  var msg = status == Status.running ? "Program running" : "Idle";

  print(msg);
}
