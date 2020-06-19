#include "ctl.h"
// Example of use of ctl.
// This code will print Fibonacci numbers at compile-time.

// A parametrized struct to generate Fibonacci numbers at compile-time.
template<unsigned N>
struct fib
{
    static const int val = fib<N - 1>::val + fib<N - 2>::val;
};

template<>
struct fib<1>
{
    static const int val = 1;
};

template<>
struct fib<0>
{
    static const int val = 0;
};

// A functor struct used to print the Fibonacci numbers.
template<unsigned N>
struct print_fib
{
    constexpr void operator()() const noexcept
    {
        std::cout << fib<N>::val << ' ';
    }
};

// This functor is used in a compile-time while loop, it will generate fibonacci numbers using a O(n) algorithm
// The action functor for a while loop must return a std::integer_sequence with all loop parameters in it
template<int a, int b, int max>
struct action
{
    constexpr auto operator()() const noexcept
    {
        std::cout << a << ' ';
        return std::integer_sequence<int, b, a + b, max>{};
    }
};

// This functor is the test condition for the while loop
// (note that some template arguments are not used in the condition but are still required)
template<int a, int b, int max>
struct condition
{
    constexpr bool operator()() const noexcept
    {
        return a < max;
    }
};

// A function used to illustrate the make_action_functor struct
void print_something(int x)
{
    std::cout << "\nNumber " << x;
}

int main()
{
    std::cout << "Prints the first 20 Fibonacci numbers (in a very non-efficient way):\n";
    ctl::for_loop<unsigned, 0, 20,
            ctl::utils<unsigned>::update_functors<1>::inc,
            ctl::utils<unsigned>::less_than,
            print_fib>::begin();

    //This is an example of conversion of a function (print_something) to a functor
    ctl::for_loop<int, 0, 10,
            ctl::utils<int>::update_functors<1>::inc,
            ctl::utils<int>::less_than,
            ctl::make_action_functor<int, print_something>::instance>::begin();

    std::cout << "\n\nWe can also do it with a ctl::while_loop, printing the Fibonacci numbers smaller than 10000\n";
    std::cout << "This way we can calculate the numbers non-recursively:\n";
    ctl::while_loop<int, condition, action, 0, 1, 10000>::begin();

    std::cout << "\n\nAnd this is a do-while loop (the loop has a false starting condition):\n";
    ctl::while_loop<int, condition, action, 10000, 15000, 10000>::do_while_begin();
}

