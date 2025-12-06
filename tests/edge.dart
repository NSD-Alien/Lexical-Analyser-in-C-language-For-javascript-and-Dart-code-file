// Dart Edge-Case Stress Test — 150+ lines
// Features: async, sync*, async*, cascades, weird strings, unicode identifiers,
// raw strings, multiline, nested comments, operator overloads, enums, extensions,
// malformed constructs, mixins, generics, null-safety edge cases, metadata annotations.

import 'dart:math' as math;

/* Nested comment test
   /* Inner comment */
   Back to outer
*/

const PI_VAL = 3.14159;
final emojiVar = "😀";
var αβγ = 42;         // Unicode identifiers
var list = [1, 2, 3];
var map = {"key": "value"};

String? maybeString;

enum Status { idle, running, failed }

class Weird<T extends num> {
  T value;
  Weird(this.value);

  T doubled() => (value * 2) as T;

  @override
  String toString() => "Weird<$T>(value=$value)";
}

mixin Talker {
  void speak(String msg) {
    print("Speaking: $msg");
  }
}

class Person with Talker {
  final String name;
  int age;
  Person(this.name, this.age);

  void info() => print("Name: $name, Age: $age");
}

// Extension test
extension StringX on String {
  String reversed() => split("").reversed.join();
}

// Operator overloading
class Vec {
  final int x, y;
  const Vec(this.x, this.y);

  Vec operator +(Vec v) => Vec(x + v.x, y + v.y);
  Vec operator -(Vec v) => Vec(x - v.x, y - v.y);
  @override
  String toString() => "Vec($x, $y)";
}

// Multiline string
var poem = """
Roses are red,
Violets are blue,
Dart is fun,
And so are you.
""";

// Raw string edge cases
var rawStr = r"This has \n no escapes \t or unicode \u1234";

// Interpolation edge-cases
var tricky = "Value: ${math.pow(2, 10)}, weird calc: ${(() => 5 + 6)()}";

Future<int> asyncAdder(int a, int b) async {
  await Future.delayed(Duration(milliseconds: 1));
  return a + b;
}

Stream<int> countStream(int max) async* {
  for (var i = 0; i < max; i++) {
    yield i;
  }
}

// Complex async*
Stream<String> weirdStream() async* {
  yield "Start";
  await Future.delayed(Duration(milliseconds: 1));
  yield* Stream.value("Middle");
  yield "End";
}

// Cascades
void cascadeTest() {
  var sb = StringBuffer()
    ..write("Hello ")
    ..write("World ")
    ..write("from cascades!");

  print(sb.toString());
}

// Weird whitespace
  int    spaced   ( int   a ,    int b     )
{      return  a     +   b    ; }

// Generics + edge cases
List<T> makeList<T>(T value, int count) {
  return List.generate(count, (_) => value);
}

// Function with default function parameter
void func(fun([int x = 10]) = print) {
  fun("Default exec: $x"); // x from parameter default
}

// Intentional malformed escapes
var bad1 = "\q invalid";
var bad2 = "\uXYZW";

// Edge-case type tests
bool testNulls() {
  String? s = null;
  return s?.length == null;
}

// Nested raw + multi-line strings
var crazy = r"""
Raw multi-line
with \n not interpreted
and ${"interpolation"} ignored
""";

// Extra filler to exceed 150 lines
void filler() {
  int sum = 0;
  for (int i = 0; i < 120; i++) {
    sum += i;
  }
  print(sum);
}

// Main function
void main() async {
  var p = Person("Alice", 30);
  p.info();
  p.speak("Hello!");

  print(Weird<int>(5).doubled());

  print("abc".reversed());

  cascadeTest();

  var v1 = Vec(1, 2);
  var v2 = Vec(3, 4);
  print(v1 + v2);
  print(v2 - v1);

  print(await asyncAdder(10, 20));

  await for (var v in countStream(5)) {
    print(v);
  }

  await for (var msg in weirdStream()) {
    print(msg);
  }

  filler();
}
