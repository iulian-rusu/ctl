# Compile-Time Loops in C++

Some playing around with template metaprogramming in C++.
The `main.cpp` file contains a driver program that will print some of the Fibonacci sequence, all the numbers being calculated at compile-time.
The focus of the test program is not efficiency, as there are far better ways to calculate the Fibonacci numbers that do no involve recursion.
It is meant to show the difference between a run-time and compile-time recursive calculation of the Fibonacci numbers.

The functionality is achieved with some template tricks and using C++17's `if constexpr`. 
A run-time recursive algorithm will usually take several seconds to calculate the first 40 Fibonacci term, using `ctl::for_loop` will print the answer almost immediately,
at the cost of a small compilation overhead. You can also use `ctl::while_loop` to calculate the numbers easier.

