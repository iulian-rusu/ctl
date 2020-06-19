#ifndef CTL_H
#define CTL_H

#include <utility>
#include "ctl/utils.h"
#include "ctl/make_functor.h"
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
    template<typename T,
            T I,
            T N,
            template<T> typename update_functor,
            template<T, T> typename conditional_functor,
            template<T> typename action_functor>
    struct for_loop
    {
        for_loop() = delete;

        /**
         * Static method used to start the loop.
         *
         * @return                  true if the loop has executed at least once, otherwise false.
         */
        static constexpr bool begin() noexcept
        {
            if constexpr (conditional_functor<I, N>{}())
            {
                action_functor<I>{}();
                for_loop<T, update_functor<I>{}(), N, update_functor, conditional_functor, action_functor>::begin();
                return true;
            }
            return false;
        }
    }; // struct for_loop

    /**
     * Struct used to expand a while loop at compile-time.
     *
     * @tparam T                    The type used to iterate through the loop.
     * @tparam conditional_functor  A functor used to verify if the loop is still running.
     * @tparam action_functor       A functor that performs the action on each iteration.
     * @tparam Args                 A pack of template arguments that represents the initial values of all loop parameters.
     */
    template<typename T,
            template<T ...> typename conditional_functor,
            template<T ...> typename action_functor,
            T ... Args>
    struct while_loop
    {
        while_loop() = delete;

        /**
         * Static method used to start the loop.
         *
         * @return                  true if the loop has executed at least once, otherwise false.
         */
        static constexpr bool begin() noexcept
        {
            if constexpr (conditional_functor<Args ...>{}())
            {
                next_iter(action_functor<Args ...>{}());
                return true;
            }
            return false;
        }

        /**
        * Static method used to start a do-while type loop.
        *
        * @return                  always true.
        */
        static constexpr bool do_while_begin() noexcept
        {
            next_iter(action_functor<Args ...>{}());
            return true;
        }

        /**
         * Helper static method used to unpack the std::integer_sequence template arguments and pass them to the next iteration
         *
         * @tparam Ints             A pack of template arguments representing the current values of all loop parameters.
         */
        template<T ... Ints>
        static constexpr void next_iter(std::integer_sequence<T, Ints ...> &&) noexcept
        {
            if constexpr (conditional_functor<Ints ...>{}())
                next_iter(action_functor<Ints ...>{}());
        };
    };// struct while_loop
} // namespace ctl
#endif // CTL_H
