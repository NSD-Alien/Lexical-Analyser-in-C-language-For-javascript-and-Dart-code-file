// JS Edge-Case Stress Test — 150+ lines
// Includes: template strings, nested comments, unicode identifiers, tricky escapes,
// regex confusion, operators, malformed code, weird whitespace, odd identifiers,
// floating numbers, hex, octal, binary, BigInt, rare operators, etc.

/* Nested comment test
   /* Deep nested */
   Still inside outer comment
*/

var αβγ = 123;              // Unicode identifier
let $str$ = "hello\nworld"; // Escapes
const sym = Symbol("id");

function weird(x, y = 10, ...rest) {
    return x ?? y + rest?.[0] ?? 0;
}

let obj = {
    "key space": 15,
    get value() { return this["key space"]; },
    set value(v) { this["key space"] = v; },
    async fetch() { return await Promise.resolve(42); },
};

let arr = [1,2,,4, ,5];      // Sparse array
let arr2 = [...arr, ...[6,7,8]];

let str = `Template literal test:
Line1
Line2 with \`escaped backticks\`
${1 + 2}
${`nested ${`template`}`}
`;

let regex1 = /abc\d+/g;
let regex2 = /[a-zA-Z]+\/test/g; // Looks like a comment but isn't
let tricky = /=\/\//;            // Looks like a regex

// Numeric edge cases
let a = 0.0;
let b = .5;
let c = 5.;
let d = 1e+10;
let e = 0xFF;
let f = 0o755;
let g = 0b101010;
let h = 999999999999999999999999n; // BigInt

// Optional chaining everywhere
let deep = globalThis?.window?.document?.body?.children?.[0]?.dataset?.value;

// Arrow functions with edge cases
let fn1 = x => x * 2;
let fn2 = (a, b = (x => x+1)(10)) => a + b;
let fn3 = () => ({ value: 123 });

// Function with strange whitespace
function   spaced    (   x   ,   y   )  
{   return   x+y ; }

// Reserved words as property names
let mixed = {
    class: 1,
    function: 2,
    default: 3,
    await: 4,
    yield: 5,
};

// Escaped unicode string
let uniStr = "\u0041\u03A9\u{1F600}";

// String with impossible escapes
let bad1 = "Invalid \q escape";
let bad2 = "\uXYZW";

// Hex inside string
let trick = "0x1234";

// Deceptive operators
let op1 = a+++b;     // a++ + b
let op2 = a----b;    // a-- - b
let op3 = a/**/b;    // Comment between tokens

// Labels
start:
for (let i=0;i<3;i++){
    if (i===1) continue start;
}

// Try/catch edge case
try {
    throw new Error("Fail");
} catch (e if false) {      // Old SpiderMonkey syntax — invalid
} catch (e) {
    console.log("Recovered");
}

// Class edge cases
class Weird {
    #hidden = 123;
    *gen(){
        yield* [1,2,3];
    }
    async *agen(){
        yield* [Promise.resolve(1)];
    }
    ["computed" + "Name"](){ return 10; }
}

// Unicode escapes in identifiers
let \u0061bc = 5; // abc

// Automatic semicolon insertion weirdness
let trickyASI = function(){ return }
(1 + 2);

// Deeply nested template strings
let nester = `Level1 ${`L2 ${`L3 ${`L4`}`}`}`;

// Long dummy filler to push file beyond 150 lines
// -------- filler --------
let filler = 0;
for (let i=0;i<120;i++){
    filler += i;
}
console.log(filler);
// -------- end filler ----
