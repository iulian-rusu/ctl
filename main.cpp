#include "ctl/ctl.h"
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
template<unsigned N>
struct print_fib
{
    void operator()() const noexcept
    {
        std::cout << "Fib<" << N << "> = " << Fib<N>::val << '\n';
    }
};

// This functor will generate a sequence of indices according to a polynomial formula
template<unsigned I>
struct poly_recursive
{
    constexpr unsigned operator()() const noexcept
    {
        return 2 * I + 1;
    }
};

int main()
{

    std::cout << "Prints the Fibonacci numbers from 0 to 19:\n";
    ctl::for_loop<unsigned, 0, 20, ctl::utils<unsigned>::updaters<1>::inc, ctl::utils<unsigned>::less_than, print_fib>::begin();

    std::cout << "And this prints some of them in reverse with a step of 2:\n";
    ctl::for_loop<unsigned, 25, 10, ctl::utils<unsigned>::updaters<2>::dec, ctl::utils<unsigned>::greater_than, print_fib>::begin();

    std::cout << "And this will print some Fibonacci numbers in a more complicated pattern\n";
    ctl::for_loop<unsigned, 0, 40, poly_recursive, ctl::utils<unsigned>::less_than, print_fib>::begin();
}

