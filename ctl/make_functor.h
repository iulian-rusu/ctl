#ifndef CTL_MAKE_FUNCTOR_H
#define CTL_MAKE_FUNCTOR_H
/**
 * make_functor - API to convert functions into functors used by ctl.
 * Only creates functors for ctl::for_loop.
 */

/**
 * A few structs that will take a type and a function pointer as template parameters and generate a functor based on that.
 */
namespace ctl
{
    template<typename T, T (*func)(T)>
    struct make_update_functor
    {
        template<T I>
        struct instance
        {
            constexpr T operator()() const noexcept
            {
                return func(I);
            }
        };
    };

    template<typename T, void (*func)(T)>
    struct make_action_functor
    {
        template<T I>
        struct instance
        {
            constexpr void operator()() const noexcept
            {
                func(I);
            }
        };
    };

    template<typename T, bool (*func)(T, T)>
    struct make_conditional_functor
    {
        template<T I, T N>
        struct instance
        {
            constexpr bool operator()() const noexcept
            {
                return func(I, N);
            }
        };
    };
} // namespace ctl
#endif //CTL_MAKE_FUNCTOR_H
