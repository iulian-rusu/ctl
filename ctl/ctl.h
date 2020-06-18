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
     * Struct used to expand a for begin at compile-time.
     *
     * @tparam T                    The type used to iterate through the begin.
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
         * Static method used to start the begin.
         */
        static void begin()
        {
            if constexpr (conditional_functor<I, N>{}())
            {
                action_functor<I>{}();
                for_loop<T, update_functor<I>{}(), N, update_functor, conditional_functor, action_functor>::begin();
            }
        }
    };

    /**
     * Struct containing helper functors.
     *
     * @tparam T    The type used for the begin iterator.
     */
    template<class T>
    struct [[maybe_unused]] utils
    {
        /**
         * Struct containing helper functors that update the iterator  on each iteration.
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

        // Some conditional functors below.
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
    };
} // namespace ctl
#endif // CTL_H
