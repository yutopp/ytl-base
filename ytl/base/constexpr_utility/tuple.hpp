#if !defined(YTL_OLD_IMPL)

#ifndef YTL_BASE_CONSTEXPR_UTILITY_TUPLE_HPP
#define YTL_BASE_CONSTEXPR_UTILITY_TUPLE_HPP

#include <type_traits>

#include "../config.hpp"

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


        namespace detail
        {
            template<bool HasType, std::size_t Index>
            struct found_type_index_value {};


            template<typename To, std::size_t N>
            struct type_indexer
            {
                template<std::size_t Index, typename T, typename... Ts>
                YTL_CONSTEXPR auto probe() const
                    -> typename std::enable_if<
                            std::is_convertible<To, T>::value,
                            found_type_index_value<true, Index>
                       >::type
                {
                    return found_type_index_value<true, Index>();
                }

                template<std::size_t Index, typename T, typename... Ts>
                YTL_CONSTEXPR auto probe() const
                    -> typename std::enable_if<
                            !std::is_convertible<To, T>::value,
                            decltype( type_indexer<To, N - 1>().template probe<Index + 1, Ts...>() )
                       >::type
                {
                    return type_indexer<To, N - 1>().template probe<Index + 1, Ts...>();
                }
            };

            template<typename To>
            struct type_indexer<To, 0>
            {
                template<std::size_t Index, typename T>
                YTL_CONSTEXPR auto probe() const
                    -> typename std::enable_if<
                            std::is_convertible<To, T>::value,
                            found_type_index_value<true, Index>
                       >::type
                {
                    return found_type_index_value<true, Index>();
                }

                template<std::size_t Index, typename T>
                YTL_CONSTEXPR auto probe() const
                    -> typename std::enable_if<
                            !std::is_convertible<To, T>::value,
                            found_type_index_value<false, 0>
                       >::type
                {
                    return found_type_index_value<false, 0>();
                }
            };
        } // namespace detail

        // find type index
        template<typename To, typename... Ts>
        YTL_CONSTEXPR auto find_type_index()
            -> typename std::enable_if<
                    ( sizeof...(Ts) > 0 ),
                    decltype( detail::type_indexer<To, ( sizeof...(Ts) - 1 )>().template probe<0, Ts...>() )
               >::type
        {
            return detail::type_indexer<To, ( sizeof...(Ts) - 1 )>().template probe<0, Ts...>();
        }


/*
    {
        YTL_CONSTEXPR ytl::cu::tuple<bool, int, double> const s( true, 72, 3.14  );
        static_assert( ytl::cu::get<0>( s ) == true, "" );
        static_assert( ytl::cu::get<1>( s ) == 72, "" );
        static_assert( ytl::cu::get<2>( s ) == 3.14, "" );

        static_assert( ytl::cu::tuple<bool, int, double>::element_num == 3, "" );
    }

    {
        ytl::cu::tuple<bool, int, double> const s( true, 72, 3.14  );
        assert( ytl::cu::get<0>( s ) == true );
        assert( ytl::cu::get<1>( s ) == 72 );
        assert( ytl::cu::get<2>( s ) == 3.14 );
    }
*/

    } // namespace cu
} // namespace ytl

#endif /*YTL_BASE_CONSTEXPR_UTILITY_TUPLE_HPP*/

#endif /*!defined(YTL_OLD_IMPL)*/