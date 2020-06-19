#include "ctl/ctl.h"
// Example of use of ctl.
// This code will print Fibonacci numbers at compile-time.

// A parametrized struct to generate Fibonacci numbers at compile-time.
template<size_t N>
struct fib
{
    static const int val = fib<N - 1>::val + fib<N - 2>::val;
};

// A couple of template specializations for the first two numbers in the sequence.
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

// A functor struct used to print the numbers.
// This struct must depend on a template parameter the is compatible with the update and conditional functor.
template<unsigned N>
struct print_fib
{
    void operator()() const noexcept
    {
        std::cout << "fib<" << N << "> = " << fib<N>::val << '\n';
    }
};

// This functor will generate a sequence of indices according to a polynomial formula
template<int I>
struct poly_recursive
{
    constexpr int operator()() const noexcept
    {
        return 5 * I + 2;
    }
};

// Action functor that creates another loop inside of the main loop
template<int I>
struct nested_loop
{
    void operator()() const noexcept
    {
        if (ctl::for_loop<int, I, 0,
                ctl::utils<int>::updaters<2>::dec,
                ctl::utils<int>::greater_than,
                ctl::utils<int>::out<>::print_index>::begin())
            std::cout << '\n';
    }
};

int main()
{

    std::cout << "Prints the Fibonacci numbers from 0 to 19:\n";
    ctl::for_loop<unsigned, 0, 20, ctl::utils<unsigned>::updaters<1>::inc, ctl::utils<unsigned>::less_than, print_fib>::begin();

    std::cout << "\nAnd this prints some of them in reverse with a step of 2:\n";
    ctl::for_loop<unsigned, 25, 10, ctl::utils<unsigned>::updaters<2>::dec, ctl::utils<unsigned>::greater_than, print_fib>::begin();

    std::cout << "\nThis will print a more complicated sequence of numbers to std::cout, separated by a space:\n";
    ctl::for_loop<int, 0, 99999999, poly_recursive, ctl::utils<int>::less_than, ctl::utils<int>::out<>::print_index>::begin();

    std::cout << "\n\nAnd this will make two nested for loops, where the inner one depends on the outer one:\n";
    ctl::for_loop<int, 0, 10, ctl::utils<int>::updaters<1>::inc, ctl::utils<int>::less_than, nested_loop>::begin();
}

