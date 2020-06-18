#ifndef CTL_H
#define CTL_H

#include <iostream>
#include <algorithm>

/**
 * ctl - a Compile-Time Loop header designed to help expand for loops at compile-time.
 */

namespace ctl
{
    /**
     * Class used to expand a for loop at compile-time.
     *
     * @tparam T                    The type used to iterate through the loop.
     * @tparam I                    The starting value of the counter.
     * @tparam N                    The value at which when the counter stops.
     * @tparam update_functor       A functor used to update the counter on each iteration.
     * @tparam conditional_functor  A functor used to verify the stop condition.
     * @tparam action_functor       A functor that performs the action on each iteration.
     */
    template<class T,
            T I,
            T N,
            template<T> class update_functor,
            template<T, T> class conditional_functor,
            template<T> class action_functor>
    class [[maybe_unused]] for_loop
    {
    public:
        for_loop() = delete;// To avoid initialization.

        /**
         * Static method used to start the loop.
         */
        static void loop()
        {
            if constexpr (conditional_functor<I, N>{}())
            {
                action_functor<I>{}();
                for_loop<T, update_functor<I>{}(), N, update_functor, conditional_functor, action_functor>::loop();
            }
        }
    };

    /**
     * Class containing helper functors used for loops.
     *
     * @tparam T    The type used in the for loop counter.
     */
    template<class T>
    class utils
    {
    public:
        template<T I>
        class increment
        {
        public:
            constexpr size_t operator()() const noexcept
            {
                return I + 1;
            }
        };

        template<T I>
        class decrement
        {
        public:
            constexpr size_t operator()() const noexcept
            {
                return I - 1;
            }
        };

        template<T I, size_t N>
        class less_than
        {
        public:
            constexpr bool operator()() const noexcept
            {
                return I < N;
            }
        };

        template<T I, size_t N>
        class greater_than
        {
        public:
            constexpr bool operator()() const noexcept
            {
                return I > N;
            }
        };
    };
} // namespace ctl
#endif // CTL_H
