#include "ctl.h"
// Example of use of ctl.
// This code will print Fibonacci numbers at compile-time.

// A parametrized struct to generate Fibonacci numbers at compile-time.
template<size_t N>
struct Fib
{
    static const int val = Fib<N - 1>::val + Fib<N - 2>::val;
};

// A couple of template specializations for the first two numbers in the sequence.
template<>
struct Fib<1>
{
    static const int val = 1;
};

template<>
struct Fib<0>
{
    static const int val = 0;
};

// A functor class used to print the numbers.
// This class must depend on a size_t template parameter.
template<size_t N>
struct print_fib
{
    void operator()() const noexcept
    {
        std::cout << "Fib<" << N << "> = " << Fib<N>::val << '\n';
    }
};

int main()
{
    // Prints the Fibonacci numbers from 0 to 19
    // The values are calculated at compile-time
    // ctl::utils<size_t>::increment increments the counter by 1 each iteration
    // ctl::utils<size_t>::less_than cheks if the counter is less than 20
    ctl::for_loop<size_t, 0, 20, ctl::utils<size_t>::increment, ctl::utils<size_t>::less_than, print_fib>::loop();

    // This is how to print them in reverse from 25 to 21
    ctl::for_loop<size_t, 25, 20, ctl::utils<size_t>::decrement, ctl::utils<size_t>::greater_than, print_fib>::loop();
}

