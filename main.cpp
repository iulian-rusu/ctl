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
    void operator()() const noexcept
    {
        std::cout << fib<N>::val << ' ';
    }
};

// This functor is used in a compile-time while loop, it will generate fibonacci numbers using a O(n) algorithm
// The action functor for a while loop must return a std::integer_sequence with all loop parameters in it
template<int a, int b, int max>
struct action
{
    auto operator()()
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
    constexpr bool operator()()
    {
        return a < max;
    }
};


int main()
{
    std::cout << "Prints the first 20 Fibonacci numbers (in a very non-efficient way):\n";
    ctl::for_loop<unsigned, 0, 20, ctl::utils<unsigned>::updaters<1>::inc, ctl::utils<unsigned>::less_than, print_fib>::begin();

    std::cout << "\n\nWe can also do it with a ctl::while_loop, printing the Fibonacci numbers smaller than 10000\n";
    std::cout << "This way we can calculate the numbers non-recursively:\n";
    ctl::while_loop<int, condition, action, 0, 1, 10000>::begin();

}

