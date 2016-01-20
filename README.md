# Swift Application

https://gist.github.com/mookerji/ef85e76e8bbfb6539643

## Software, Product, and Embedded Engineering Candidates

In the programming language of your choice, write a program
generating the first n Fibonacci numbers F(n), printing ...
- ... "Buzz" when F(n) is divisible by 3.
- ... "Fizz" when F(n) is divisible by 5.
- ... "BuzzFizz" when F(n) is prime.
- ... the value F(n) otherwise.

Bonus points for efficient implementation, testing, documentation,
and/or upload your code to GitHub.

## Build

- $ make
- $ ./unit_tests to run the tests
- $ ./main to run the main program

## Program

Print one line per fibonacci element until.
Will print:
- Buzz if Fn is divisible by 3
- Fizz if Fn is divisible by 5
- BuzzFizz if Fn is prime
If Fn matches several cases, they will be printed on the same line.
Usage:  ./main last_index [-v]

## Features

- Detects overflows
- Optimized prime testing using Eratosthenes and Fibonacci's divisibility properties

## TODO

- Use Big Integers to go beyond F93
- Optimize Eratosthenes to use bits instead of bools
- Add thread safety
