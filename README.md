# Building A Bytecode Virtual Machine
This program is a virtual machine for a custom scripting language called Lox. Lox is a high-level, dynamically-typed[^1] language like Python or PHP. Since Lox is a scripting language, it executes directly from source.

This program is represented using bytecode, rather than abstract syntax trees using Java. Bytecode resembles machine code in the sense that it is a linear sequence of binary instructions. This representation has low overhead and uses the cache efficiently.

For this project, I used a book called Crafting Interpreters by Robert Nystrom, where an interpreter is built from the ground up.[^2] It is ideal to get a better understanding of how high-level languages are implemented, and what goes through the creation of an interpreter using popular programming languages like Java or C. This is a project to document what I learned.

# Lox Documentation
This reference manual describes the Lox programming language implemented in C.

In Lox, values are created by literals, computed by expressions, and stored in variables. But the user only sees Lox objects (that are implemented in the undrelying language the interpreter is written in, aka Java).

### Keywords
The following identifiers are used as reserved words, or Lox _keywords_, and cannot be used as ordinary identifiers.
```
and         fun         or          this
class       for         print       true
else        if          return      var
false       nil         super       while
```

### Literals
Literals are notations for constant values of some built-in types. A literal can be a user-defined identifier, a string, or a number.

#### String Literals
These are literals for a string value, and it is defined by putting quotation marks around the literal.
```
text = "Example text";
```

#### Numeric Literals
All numbers in Lox are floating point at runtime, but both integer and decimal literals are supported. Lox doesn't allow leading or trailing decimal point, which means that `.1234` and `1234.` are not valid.

Note that numeric literals do not include a sign; a phrase like `-1` is an expression formed by the unary operator `-` and the literal `1`.

#### Identifiers
Users can define and use their own identifiers using the `var` keyword. The location in which these identifiers are declared will affect the scope of where they can and cannot be used. Global identifiers are defined inside of a class, and can be used anywhere in the class. Local identifiers are defined inside of a function or method, and can only be used in that function or method.
```
class myFirstClass
{
    var globalIden = "I'm global";      // A global identifier.

    ...
}
```
```
fun myFirstFun()
{
    var localIden = "I'm local";        // A local identifier.

    ...
}
```

### Operators
The following tokens are operators in Lox.
```
+           -           *           /
<           >           ;           //
<=          >=          ,           .
!=          ==          =
```

### Delimeters
The following tokens serve as delimiters in the grammar.
```
(           )
{           }
```

### Objects
Objects are Lox's abstraction for data. All data in Lox is represented by objects or by relations between objects.

In Lox, values are created by literals, computed by expressions, and stored in variables. But the user only sees Lox objects (that are implemented in the undrelying language the interpreter is written in, aka Java).

### Functions
Functions are declared with the `fun` keyword followed by the name of the function and a set of parentheses containing the arguments (if any). Lox functions cannot accept more than 255 arguments.
```
fun helloWorld()
{
    print "Hello World!";
}
```

### Classes
Classes are declared with the `class` keyword followed by the name of the class and a curly-braced body.
```
class myFirstClass
{
    ...
}
```

#### Class Instances
A class instance is created by calling a class object. New class instances are declared with the class name followed by a set of parenthesis.
```
class Student{}
var student = Student();
```

#### Constructor/Initializer
When a new class instance is created, the object is initialized with its `init()` method.
```
class Student
{
    init()
    {
        ...
    }
}
```
Returning a value from an initializer is not allowed, but using an empty `return` is permitted. If the initializer encounters an early return statement, it returns `this` object.

#### This
The keyword `this` is used to refer an object to itself to access its fields or methods.
```
class Student
{
    var age;

    init(age)
    {
        this.age = age;
    }
}
```

#### Inheritance
A class can extend another class with the token `<` after the class name, followed by the name of the parent class.
```
class Person
{
    ...
}

class Student < Person
{
    ...
}
```
When inheriting from a class, the subclass is a subtype of the superclass (or the child is a subtype of the parent). All the methods and data from the parent class can also be found in the child.

#### Methods
Unlike function declarations, methods don't have a leading `fun` keyword. Each method is a name, parameter list and body.

```
class Person
{
    drive()
    {
        ...
    }
}
```

#### Super
If a method with the same name exists in both the subclass and the superclass, the subclass takes precedence (or overrides) the superclass method. The `super` keyword is used if the user wants to refine the superclass's behavior, rather than completely replacing it. It tells the program to look for this method in the superclass and ignore any overrides.
```
class Person
{
    read()
    {
        ...     // Implementation of how an average person reads.
    }
}

class Student < Person
{
    read()
    {
        super.read();   // Implementation of how an average person reads,
        ...             // plus how a student reads.
    }
}
```

# Implementation
The instructions generated are stored in a dynamic array since we don't know how big the array needs to be before compiling a chunk. This dynamic array is grown or shrunk by the function `reallocate`, which changes the size of an allocation and allocates more memory or frees it if necessary.

While an assembler translates assembly instructions into binary machine code, a disassembler translates binary machine code into readable assembly instructions. This helps with the testing and debugging phases of the program.

Bytecode allows instructions to have operands, which are stored as binary data immediately after the opcode. For example, if the instruction opcode for loading a constant is `00` and the constant index is `23`, then the instruction would be stored as `0023` where `00` is one byte and `23` is another byte. Each opcode determines how many operand bytes the instruction has and what they mean.

Each chunk stores a separate array of integers that parallels the bytecode array. Each number in the array is the line number for the corresponding byte in the bytecode. When a runtime error occurs, we look up the line number at the same index as the current instruction's offset in the code array.








## Scanner
The first step in any interpreter (or compiler) is scanning. A scanner takes in raw source code as a stream of characters and groups them into a series of chunks called tokens. Tokens are recognized characters in programming languages like `(` or `;`, numbers, string literals, and identifiers. Tokens make up the language's grammar and they are what the scanner will feed into the parser.

It is important to understand that lexemes are sequences of characters that match the pattern for a token, and are identified as an instance of that particular token. Simply put, lexemes are the words derived from the character input stream while tokens are lexemes mapped into a token-name and an attribute-value.

The core of the scanner is a loop. Starting at the first character of the source code, the scanner will go through each one and idenfity what lexeme the character belongs to. Then it will consume the character and any following characters that are part of that lexeme. When it reaches the end of that lexeme, it creates a token. The scanner will continue to consume lexemes and occasionally emit tokens until it reaches the end of the file.

Reserved keywords like `while`, `or`, `fun`, etc. are scanned differently from operators like `<`, `>=`, or `==`. This is in order to avoid confusing the program between possible variable names and keywords. For example, if we wanted to define the variable name `orbit` and the program scanned the reserved keyword `or` character by character, then it would consider that we are trying to use the keyword `or`, and would treat the rest of the word `bit` like a variable. Instead, the program follows the principle of maximal munch, which defines that whenever we have two lexical grammar rules that match a chunk of code, whichever one matches the most characters wins. So if the rule states that we can match `orbit` as an identifier and `or` as a keyword, the former takes precedence over the latter.

## Parser
A parser takes the sequence of tokens and builds a tree structure with them. These trees are called parse trees or abstract syntax trees.
Given a series of tokens, the tokens are mapped to the terminals in the grammar to figure out which rules could have generated that string. This is done in order to understand what part of the language each token belongs to. The parser could also categorize tokens from the raw lexeme by comparing the strings, character by character. But that would be a really slow and inefficient solution.

While the lexical grammar used for the scanner was called a _regular language_, the parser uses _syntactic grammar_ to define an infinite set of strings that are in the grammar. Put another way, in order to move from the scanner to the parser, we need another level of granularity. In the scanner's grammar, the "alphabet" consists of individual characters and the strings are the valid lexemes. But in the parser's grammar, now individual tokens can be thought of as "letters" in the alphabet while strings are individual expressions made by a sequence of tokens. This subtle but critical distinction helps us separate each lexeme, token, and expression before using them in the interpreter.

A parser uses production rules to represent and organize grammars that contain an infinite number of valid strings. Production rules generate strings in the grammar and contain two elements - terminals and nonterminals. A terminal is an individual lexeme. They are called terminals because they don't produce other rules in the grammar. A nonterminal however, references another rule in the grammar. It esentially plays that rule and inserts whatever it produces there.

This is an example of a set of production rules, where terminals are quoted strings and nonterminals are lowercase words:
```
breakfast -> protein "with" breakfast "on the side" ;
breakfast -> protein ;
breakfast -> bread ;

protein -> crispiness "crispy" "bacon" ;
protein -> "sausage" ;
protein -> cooked "eggs" ;

crispiness -> "really" ;
crispiness -> "really" crispiness ;

cooked -> "scrambled" ;
cooked -> "poached" ;
cooked -> "fried" ;

bread -> "toast" ;
bread -> "biscuits" ;
bread -> "English muffin" ;
```

Just like in the example above, the grammar that represents expressions like `grouping`, `unary`, and `binary`, is recursive by nature. This is because the expression refers to itself or to another expression, and it is the reason why the data structure will form a (syntax) tree.

A parser has two jobs:
1. To produce a corresponding syntax tree given a valid sequence of tokens.
2. To detect any errors and notify the user if the sequence of tokens is invalid.

The most important aspect of a parser is usability because at the end of the day, the user is the one who will be dealing with it the most. If the parser takes a long time to consume all the source files or if it doesn't notify the user of their mistakes, then it is not very usable. This is why the parser reports as many separate errors as it can while ignoring cascaded errors (meaning that it ignores the errors that are a side effect of previous errors).

## Interpreter
Each kind of expression in Lox behaves differently at runtime, which means that the interpreter needs to select a different chunk of code to handle each expression type. Since the tree classes are used by both the parser and the interpreter, it would be a mess to associate all their behavior using methods on the classes themselves. In addition, doing name resolution on all those classes every time we need them or adding instance methods for _all_ the operations we need to perform over different domains would be really slow and inefficient; and it would violate separation of concerns. 

Instead, the best way to model syntax tree nodes is by using the Visitor pattern, which combines functional and object-oriented programming. With this design choice, we can define all of the behavior for a new operation on a set of types (in this case multiple different classes) in one place, without having to touch the types themselves. So we define a separate interface, and each operation that can be performed on expressions is a new class that implements that interface. To perform an operation on an expression, we call its `accept()` method and pass in the visitor for the operation we want to execute. That way we can use that method for as many visitors as we want without ever having to touch the expression classes again.

The leaves of an expression tree are literals. A literal is a bit of syntax that produces a value when it is evaluated at runtime. During scanning, the program produces the runtime value and puts it in a token that is later consumed by the parser. So the interpreter simply pulls it back out when evaluating the literal.

To evaluate a grouping expression, the interpreter recursively evaluates the subexpression inside. This subexpression is what exists inside the parantheses.

Like grouping expressions, unary expressions have a single subexpression that needs to be evaluated first. Once the operand expression is evaluated, the unary operator is applied to the result.

Unlike unary expressions, binary expressions have two operands to evaluate using the appropriate operator.

An expression statement can be defined as an expression that has side effects, such as calling a function or a method, or declaring variables. For example, a print statement evaluates an expression and displays the result to the user. But unlike expressions, statements produce no values. So the interpreter evaluates the inner expression and discards the value before returning `null`.

In Lox, an environment stores the bindings that associate variables to values. It is like a map where the keys are variable names and the values are the variable's values themselves. There are different levels of environments, such that the program remembers the state of global variables, defined functions, and local variables. It also evaluates the precedence for each one using scopes and uses the right environment at runtime. Multiple scopes enable the same name to refer to different things in different contexts.

Once variable declaration, scopes, and logical operators were implemented, the program was able to execute while and for loops. Both loops require the same conditions in order to work:
1. The initializer: Executed exactly once, before anything else. It could be an expression or a variable declaration.
2. The condition: The expression that controls when to exit the loop. It is evaluated at the beginning of each iteration, including the first.
3. The increment: An arbitrary expression that does some work at the end of each loop iteration. It almost always increments a variable.
4. The body: The work that needs to be executed with each iteration.

Implementing functions took longer than any of the features we implemented before, because functions require the implementation of: 
- Variable declaration: To bind the name of the function to the actual block that executes it.
- Scopes: To keep track of what variables can and cannot be used, as well as the arguments passed by the function.
- Unary/binary expressions and conditional operators: To execute the work inside of the function.
- Return expression: To emit the result and pass it back to the user, or simply to jump back to the rest of the code if there is no return value.

A `return` statement is useful for when a function does not have a return value, but we want to exit it early. When the statement is executed, the program uses a custom exception to unwind the interpreter past the `visit` methods of all of the containing statements, back to the code that began executing the body. The custom exception class extends Java's `RuntimeException` and since we only need it to unwind the interpreter (rather than to throw an actual exception), then we use a try-catch block in the `executeBlock()` method. That way the program can catch the return exception and pull out the value from the return statement. If the program never catches one of these exceptions, then it means the function reached the end of the body without hitting a `return` statement, so it returns `nil`.

Before the Resolver class was implemented, the interpreter would resolve a variable each and every time the variable expression was evaluated. This means that if the variable was inside a loop that ran a thousand times, the variable was resolved a thousand times. A better approach is to resolve each variable once. So the Resolver class inspects the program, finds every variable mentioned, and figures out which declaration each refers to. 

While the parser tells only if a program is grammatically correct, the resolver figures out what the different pieces of the program actually mean (aka resolve variable bindings). The greatest advantage about having a resolver is that there is no control flow. Loops are visited only once and both branches are visited in `if` statements.

Each time the resolver visits a variable, it tells the interpreter how many scopes there are between the current scope and the scope where the variable is defined so that the interpreter can find the variable's value.

## Error Handling
Since it is up to the program to notify the user of anything that could have gone wrong, the program has an error function that reports to the user that there is some syntax error on a given line.

For lexical errors, if the scanner finds a character that Lox doesn't use, the erronous character gets discarded and the scanner keeps going through the characters in the source code. At the end, the program reports the all the errors to the user at one time. This is done to avoid having an error, having the program report it to the user so that it can be fixed, and then going through the same tedious process for the next error.

And to prevent the program from crashing when it detects an error in non-critical operations, the program has a flag that is activated whenever it encounters an error. That way it can still perform non-critical operations without executing any code that could end the program abruptly.

When an error occurs, the parser discards tokens until it gets to the next statement. And then it will parse the rest of the file starting at that location. This process of getting its state and the sequence of following tokens aligned such that the next token does match the rule being parsed, is called synchronization. The parser fixes its parsing state by jumping out of any nested production rules until it gets back to that rule. Then it synchronizes the token stream by discarding tokens until it reaches an expected one based on the rule. For runtime errors however, it catches the exception thrown by the language it is implemented on (Java) and notifies the user of the error that occurred.

Having a ParseError class gives us the opportunity to unwind the parser if there is an unexpected error. In fact, the `error()` method _returns_ the error as opposed to throwing it because that way, the calling method inside the parser decides whether to unwind or not. Some parse errors occur in non-critical places where the parser doesn't need to synchronize. In those places, the program simply reports the error and keeps parsing.

It is critical to detect and address runtime errors appropriately. If these errors are not handled correctly, the program will throw a Java exception that will unwind the whole stack before exiting the application and printing the Java stack trace on the screen. But the fact that Lox is implemented in Java should be a detail hidden from the user, which is why dealing with runtime errors is important. The program uses its own class to extend the functionality of Java's RuntimeException class in order to detect and report errors to the user.

Call type errors serve to detect and notify the user that the function they tried to call is not callable. An example of this are strings that are used as functions like `"not a function"();`. The program will identify that the object is not an instance of `LoxCallable` and will catch the Java exception. The interpreter will then throw a Lox exception and report it to the user.
----------------------------------------------------------

A "chunk" refers to a sequence of bytecode.



[^1]: Dynamically-typed means that the interpreter assigns variables a type at runtime based on the variable's value. This is different from a statically-typed language like Java or C, where variable types are known at compile time.

[^2]: https://craftinginterpreters.com/contents.html
