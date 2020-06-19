#ifndef CTL_UTILS_H
#define CTL_UTILS_H

#include <iostream>
/**
 * utils - Some commonly used functors for the ctl API.
 */

namespace ctl
{
    /**
     * Wrapper struct containing helper functors.
     *
     * @tparam T        The type used for the begin iterator.
     */
    template<typename T>
    struct utils
    {
        /**
         * Wrapper struct for functors that update the iterator.
         *
         * @tparam delta    The amount by which the iterator is changed.
         */
        template<T delta>
        struct update_functors
        {
            template<T I>
            struct inc
            {
                constexpr T operator()() const noexcept
                {
                    return I + delta;
                }
            };

            template<T I>
            struct dec
            {
                constexpr T operator()() const noexcept
                {
                    return I - delta;
                }
            };

            template<T I>
            struct mul
            {
                constexpr T operator()() const noexcept
                {
                    return I * delta;
                }
            };

            template<T I>
            struct div
            {
                constexpr T operator()() const noexcept
                {
                    static_assert(delta != 0, "[ctl::utils::update_functors::div]: cannot divide by 0");
                    return I / delta;
                }
            };
        }; // struct update_functors

        /**
         * Wrapper struct for functors that output something.
         *
         * @tparam sep      The character that separates the output.
         * @tparam os       A std::ostream reference where the output is directed.
         */
        template<const char sep = ' ', std::ostream &os = std::cout>
        struct output_functors
        {
            /**
             * Prints the index received as a template parameter to some specified output stream.
             *
             * @tparam I    The index to be printed.
             */
            template<T I>
            struct print_index
            {
                void operator()() const noexcept
                {
                    os << I;
                    if constexpr (sep)
                        os << sep;
                }
            };
        }; // struct output_functors

        // Conditional functors to test the loop condition.

        template<T I, T N>
        struct less_than
        {
            constexpr bool operator()() const noexcept
            {
                return I < N;
            }
        };

        template<T I, T N>
        struct greater_than
        {
            constexpr bool operator()() const noexcept
            {
                return I > N;
            }
        };

        template<T I, T N>
        struct equ
        {
            constexpr bool operator()() const noexcept
            {
                return I == N;
            }
        };

        template<T I, T N>
        struct not_equ
        {
            constexpr bool operator()() const noexcept
            {
                return I != N;
            }
        };
    }; // struct utils
} // namespace ctl
#endif //CTL_UTILS_H
