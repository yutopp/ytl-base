#include "../config.hpp"

#if !defined(YTL_OLD_IMPL)

#ifndef YTL_BASE_CONSTEXPR_UTILITY_TUPLE_HPP
#define YTL_BASE_CONSTEXPR_UTILITY_TUPLE_HPP

#include <type_traits>

namespace ytl
{
    namespace cu
    {
        template <typename... Elems> struct tuple;

        template <> struct tuple<> { /*nil*/ static YTL_CONSTEXPR std::size_t const element_num = 0; };

        template <typename Head, typename... Tail>
        struct tuple<Head, Tail...>
        {
            typedef Head                            head_type;
            typedef tuple<Tail...>                  tail_type;

            static YTL_CONSTEXPR std::size_t const  element_num = tail_type::element_num + 1;

            YTL_CONSTEXPR tuple( Head x, Tail... xs )
                : head( std::move( x ) )
                , tail( std::move( xs )... )
            {}

            head_type head;
            tail_type tail;
        };


        namespace detail
        {
            template<std::size_t I>
            struct getter
            {
                template<typename... T>
                YTL_CONSTEXPR auto operator()( tuple<T...> const& t ) const
                    -> decltype( getter<I-1>()( std::declval<typename tuple<T...>::tail_type>() ) )
                {
                    return getter<I-1>()( t.tail );
                }
            };

            template<>
            struct getter<0>
            {
                template<typename... T>
                YTL_CONSTEXPR auto operator()( tuple<T...> const& t ) const
                    -> typename tuple<T...>::head_type const&
                {
                    return t.head;
                }
            };
        } // namespace detail

        // get
        template<std::size_t I, typename... Ts>
        YTL_CONSTEXPR auto get( tuple<Ts...> const& t )
            -> decltype( detail::getter<I>()( std::declval<tuple<Ts...>>() ) )
        {
            return detail::getter<I>()( t );
        }

    } // namespace cu
} // namespace ytl

#endif /*YTL_BASE_CONSTEXPR_UTILITY_TUPLE_HPP*/

#endif /*!defined(YTL_OLD_IMPL)*/