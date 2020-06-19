#ifndef CTL_UTILS_H
#define CTL_UTILS_H

#include <iostream>

namespace ctl
{
    /**
     * Wrapper struct containing helper functors.
     *
     * @tparam T        The type used for the begin iterator.
     */
    template<typename T>
    struct [[maybe_unused]] utils
    {
        /**
         * Wrapper struct for functors that update the iterator.
         *
         * @tparam delta    The amount by which the iterator is changed.
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
        }; // struct updaters

        /**
         * Wrapper struct for functors that output something.
         *
         * @tparam sep      The character that separates the output.
         * @tparam os       A std::ostream reference where the output is directed.
         */
        template<const char sep = ' ', std::ostream &os = std::cout>
        struct [[maybe_unused]] out
        {
            /**
             * Prints the index received as a template parameter to some specified output stream.
             *
             * @tparam I    The index to be printed.
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
        }; // struct out

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
    }; // struct utils
} // namespace ctl
#endif //CTL_UTILS_H
