#ifndef CTL_H
#define CTL_H

#include <iostream>
#include <algorithm>

/**
 * ctl - Compile-Time Loops API
 */

namespace ctl
{
    /**
     * Struct used to expand a for loop at compile-time.
     *
     * @tparam T                    The type used to iterate through the loop.
     * @tparam I                    The starting value of the iterator.
     * @tparam N                    The value at which the iterator stops.
     * @tparam update_functor       A functor used to update the iterator on each iteration.
     * @tparam conditional_functor  A functor used to verify if the loop is still running.
     * @tparam action_functor       A functor that performs the action on each iteration.
     */
    template<class T,
            T I,
            T N,
            template<T> class update_functor,
            template<T, T> class conditional_functor,
            template<T> class action_functor>
    struct [[maybe_unused]] for_loop
    {
        for_loop() = delete;

        /**
         * Static method used to start the loop.
         *
         * @return true if the loop has executed at least once, otherwise false.
         */
        static constexpr bool begin()
        {
            if constexpr (conditional_functor<I, N>{}())
            {
                action_functor<I>{}();
                for_loop<T, update_functor<I>{}(), N, update_functor, conditional_functor, action_functor>::begin();
                return true;
            }
            return false;
        }
    };

    /**
     * Wrapper struct containing helper functors.
     *
     * @tparam T    The type used for the begin iterator.
     */
    template<class T>
    struct [[maybe_unused]] utils
    {
        /**
         * Wrapper struct for functors that update the iterator.
         *
         * @tparam delta  The amount by which the iterator is changed.
         */
        template<T delta>
        struct [[maybe_unused]] updaters
        {
            template<T I>
            struct [[maybe_unused]] inc
            {
                constexpr T operator()() const noexcept
                {
                    return I + delta;
                }
            };

            template<T I>
            struct [[maybe_unused]] dec
            {
                constexpr T operator()() const noexcept
                {
                    return I - delta;
                }
            };

            template<T I>
            struct [[maybe_unused]] mul
            {
                constexpr T operator()() const noexcept
                {
                    return I * delta;
                }
            };

            template<T I>
            struct [[maybe_unused]] div
            {
                constexpr T operator()() const noexcept
                {
                    static_assert(delta != 0, "[ctl::utils::updaters::div]: cannot divide by 0");
                    return I / delta;
                }
            };
        };

        /**
         * Wrapper struct for functors that output something.
         *
         * @tparam sep The character that separates the output.
         * @tparam os  A std::ostream reference where the output is directed.
         */
        template<const char sep = ' ',std::ostream &os = std::cout>
        struct [[maybe_unused]] out
        {
            /**
             * Prints the index received as a template parameter to some specified output stream.
             *
             * @tparam I The index to be printed.
             */
            template<T I>
            struct [[maybe_unused]] print_index
            {
                void operator()() const noexcept
                {
                    os << I;
                    if constexpr (sep)
                        os << sep;
                }
            };
        };

        // Conditional functors to test the loop condition.
        template<T I, T N>
        struct [[maybe_unused]] less_than
        {
            constexpr bool operator()() const noexcept
            {
                return I < N;
            }
        };

        template<T I, T N>
        struct [[maybe_unused]] greater_than
        {
            constexpr bool operator()() const noexcept
            {
                return I > N;
            }
        };

        template<T I, T N>
        struct [[maybe_unused]] equ
        {
            constexpr bool operator()() const noexcept
            {
                return I == N;
            }
        };

        template<T I, T N>
        struct [[maybe_unused]] not_equ
        {
            constexpr bool operator()() const noexcept
            {
                return I != N;
            }
        };
    };// struct utils
} // namespace ctl
#endif // CTL_H
