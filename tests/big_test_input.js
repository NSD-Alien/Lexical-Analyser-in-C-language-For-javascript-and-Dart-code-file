// tests/big_test_input.js
// Big test input for JS lexer (contains comments, declarations, mistakes, long content)

/* 
   Multi-line comment block
   Should be extracted entirely to comments.txt
*/

let count_int = 0;
let price_float = 10.5;
let name_str = "Alice";
var total = 0;
const PI_float = 3.14159;

fuinction greet() { // typo: fuinction -> function
    console.log("hi");
}

function add(a, b) {
    return a + b;
}

// Arrow function correct usage
const inc = (x) => x + 1;

// Common mistakes:
if (count_int => 10) {
    console.log("big"); // => used instead of >=
}

// More declarations
let i = 0;
for (i = 0; i < 10; i++) {
    total = total + i;
}

// nested functions and strings
function outer() {
    function inner() {
        let s = "inner string with // not a comment";
        return s;
    }
    return inner();
}

// numeric literal tests
let val_int = 42;
let val_float = 42.0;
let val_str = "42";

// assignments that trigger naming-based type check
let amount_int = 100.25;  // float assigned to _int name -> should flag
let price_float2 = 200;   // int assigned to _float name -> should flag

// Un-declared variable usage
x_undefined = 5;  // should flag

// multi-line comment start
/* This is a multi-line comment
   that spans multiple lines
   and ends here */
let a = 5;

// string with escaped quotes
let quote_str = "He said \"Hello\" to her.";

// operators and punctuation
total += val_int;
if (price_float < 300 && count_int !== 0) {
    total = total + price_float;
}

// Another mistaken keyword
retunr something; // misspelling 'return'

// More code to increase lines and cover cases
let arr = [1,2,3,4,5];
for (let idx = 0; idx < arr.length; idx++) {
    // do something
    total = total + arr[idx];
}

// function expression
const f = function(x) {
    return x * x;
}

// template literals
let tpl = `template ${name_str}`;

// complex operators
if ((a > 0) && (total <= 100)) {
    total = total - 1;
}

// intentionally add many lines to go beyond 150 total lines
// (repeat small blocks)
let z_int = 0;
let y_float = 0.0;
let s_str = "repeat";
for (let k=0; k<5; k++) {
    z_int += k;
    y_float += k * 0.5;
    s_str = s_str + "_x";
}

// more comments mixed
// another single line comment
/* second multi-line
   comment for coverage */

// end block repeated content to make file long
for (let r=0; r<10; r++) {
    let temp_int = r;
    let temp_float = r + 0.1;
    let temp_str = "x";
    // nested
    if (temp_int % 2 == 0) {
        total += temp_int;
    } else {
        total += temp_float;
    }
}

// add some edge cases
let _private = 1;
let $dollar = 2;
let camelCaseValue = 3;

// more typos and misuse
functoin wrong1() { }   // 'functoin' typo
whlie (true) { break; } // 'whlie' typo (while)
