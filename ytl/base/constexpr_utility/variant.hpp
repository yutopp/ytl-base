#include "../config.hpp"

#if !defined(YTL_OLD_IMPL)

#ifndef YTL_BASE_CONSTEXPR_UTILITY_VARIANT_HPP
#define YTL_BASE_CONSTEXPR_UTILITY_VARIANT_HPP

#include <type_traits>
#include <stdexcept>

#include "tuple.hpp"
#include "index_tuple.hpp"

namespace ytl
{
    namespace cu
    {
        namespace detail
        {
            template<bool HasType, std::size_t Index>
            struct found_type_index_value
            {
                static YTL_CONSTEXPR bool is_found = HasType;
            };


            template<template<typename, typename> class Match, typename To, std::size_t N>
            struct type_indexer
            {
                template<std::size_t Index, typename T, typename... Ts>
                YTL_CONSTEXPR auto probe() const
                    -> typename std::enable_if<
                            Match<To, T>::value,
                            found_type_index_value<true, Index>
                       >::type
                {
                    return found_type_index_value<true, Index>();
                }

                template<std::size_t Index, typename T, typename... Ts>
                YTL_CONSTEXPR auto probe() const
                    -> typename std::enable_if<
                            !Match<To, T>::value,
                            decltype( type_indexer<Match, To, N - 1>().template probe<Index + 1, Ts...>() )
                       >::type
                {
                    return type_indexer<Match, To, N - 1>().template probe<Index + 1, Ts...>();
                }
            };

            template<template<typename, typename> class Match, typename To>
            struct type_indexer<Match, To, 0>
            {
                template<std::size_t Index, typename T>
                YTL_CONSTEXPR auto probe() const
                    -> typename std::enable_if<
                            Match<To, T>::value,
                            found_type_index_value<true, Index>
                       >::type
                {
                    return found_type_index_value<true, Index>();
                }

                template<std::size_t Index, typename T>
                YTL_CONSTEXPR auto probe() const
                    -> typename std::enable_if<
                            !Match<To, T>::value,
                            found_type_index_value<false, 0>
                       >::type
                {
                    return found_type_index_value<false, 0>();
                }
            };

            template<template<typename, typename> class Match, typename To, typename... Ts>
            YTL_CONSTEXPR auto find_type_index_by_m()
                -> typename std::enable_if<
                        ( sizeof...(Ts) > 0 ),
                        decltype( detail::type_indexer<Match, To, ( sizeof...(Ts) - 1 )>().template probe<0, Ts...>() )
                   >::type
            {
                return detail::type_indexer<Match, To, ( sizeof...(Ts) - 1 )>().template probe<0, Ts...>();
            }
        } // namespace detail

        // find type index
        template<typename To, typename... Ts>
        YTL_CONSTEXPR auto find_type_index()
            -> typename std::enable_if<
                    decltype( detail::find_type_index_by_m<std::is_same, To, Ts...>() )::is_found,
                    decltype( detail::find_type_index_by_m<std::is_same, To, Ts...>() )
               >::type
        {
            return detail::find_type_index_by_m<std::is_same, To, Ts...>();
        }

        template<typename To, typename... Ts>
        YTL_CONSTEXPR auto find_type_index()
            -> typename std::enable_if<
                    !decltype( detail::find_type_index_by_m<std::is_same, To, Ts...>() )::is_found,
                    decltype( detail::find_type_index_by_m<std::is_convertible, To, Ts...>() )
               >::type
        {
            return detail::find_type_index_by_m<std::is_convertible, To, Ts...>();
        }


        // for variant detail
        namespace detail
        {
            struct decay_initializer
            {
                template<typename T>
                YTL_CONSTEXPR operator T() const { return T(); }
            };

            template<typename... N>
            struct decay_initializer_list {};


            template<std::size_t N>
            struct di_list_impl
            {
                template<typename... Ts>
                YTL_CONSTEXPR auto operator()( decay_initializer_list<Ts...> const& ) const
                    -> decltype( di_list_impl<N-1>()( decay_initializer_list<decay_initializer, Ts...>() ) )
                {
                    return di_list_impl<N-1>()( decay_initializer_list<decay_initializer, Ts...>() );
                }
            };
            template<>
            struct di_list_impl<0>
            {
                template<typename... Ts>
                YTL_CONSTEXPR auto operator()( decay_initializer_list<Ts...> const& ) const
                    -> decay_initializer_list<Ts...>
                {
                    return decay_initializer_list<Ts...>();
                }
            };

            template<std::size_t N>
            YTL_CONSTEXPR auto make_decay_initializer_list()
                -> decltype( di_list_impl<N>()( decay_initializer_list<>() ) )
            {
                return di_list_impl<N>()( decay_initializer_list<>() );
            }


            template<typename Tuple, typename... D1, typename T, typename... D2>
            YTL_CONSTEXPR auto make_intialized_tuple(
                decay_initializer_list<D1...> const&,
                T const& v,
                decay_initializer_list<D2...> const&
                )
                -> Tuple
            {
                return Tuple( D1()... , v, D2()... );
            }

            template<typename Tuple, int... Ix1, typename T, int... Ix2>
            YTL_CONSTEXPR auto make_intialized_tuple( index_tuple<int, Ix1...> const&, T const& v, index_tuple<int, Ix2...> const& )
                ->Tuple
            {
                return make_intialized_tuple<Tuple>(
                        make_decay_initializer_list<sizeof...(Ix1)>(),
                        v,
                        make_decay_initializer_list<sizeof...(Ix2)>()
                        );
            }


            template<typename Tuple, typename... Ds>
            YTL_CONSTEXPR auto make_intialized_tuple( decay_initializer_list<Ds...> const& )
                -> Tuple
            {
                return Tuple( Ds()... );
            }

            template<typename Tuple, int... Ds>
            YTL_CONSTEXPR auto make_intialized_tuple( index_tuple<int, Ds...> const& )
                ->Tuple
            {
                return make_intialized_tuple<Tuple>( make_decay_initializer_list<sizeof...(Ds)>() );
            }


            // variant impl
            template<typename... Ts>
            struct variant_impl
            {
                typedef tuple<Ts...>    tuple_type;

            public:
                template<int... Indexes>
                YTL_CONSTEXPR variant_impl( tuple_type const& tuple, index_tuple<int, Indexes...> const& )
                    : value_( get<Indexes>( tuple )... )
                    , which_( 0xffffffff )
                    , has_value_( false )
                {}

                template<int... Indexes>
                YTL_CONSTEXPR variant_impl( tuple_type const& tuple, index_tuple<int, Indexes...> const&, std::size_t const& which )
                    : value_( get<Indexes>( tuple )... )
                    , which_( which )
                    , has_value_( true )
                {}

            public:
                tuple_type value_;
                std::size_t which_;
                bool has_value_;
            };

            template<typename... Ts, typename Val, bool hasTypeValue, std::size_t Index>
            YTL_CONSTEXPR auto make_variant_impl( Val const& v, found_type_index_value<hasTypeValue, Index> const& )
                -> variant_impl<Ts...>
            {
                typedef tuple<Ts...>    tuple_type;

                return hasTypeValue
                         ? variant_impl<Ts...>(
                                detail::make_intialized_tuple<tuple_type>(
                                    make_index_tuple<int, 0, Index>(), v, make_index_tuple<int, Index+1, tuple_type::element_num>()
                                ),
                                make_index_tuple<int, 0, tuple_type::element_num>(),
                                Index
                                )
                         : throw "key not found"/**/;
            }

            template<typename... Ts>
            YTL_CONSTEXPR auto make_variant_impl()
                -> variant_impl<Ts...>
            {
                typedef tuple<Ts...>    tuple_type;

                return variant_impl<Ts...>(
                            detail::make_intialized_tuple<tuple_type>( make_index_tuple<int, 0, tuple_type::element_num>() ),
                            make_index_tuple<int, 0, tuple_type::element_num>()
                            );
            }
        } // namespace detail


        // variant
        template<typename... Ts>
        class variant
        {
            typedef typename detail::variant_impl<Ts...>::tuple_type     tuple_type;

        public:
            YTL_CONSTEXPR variant()
                : impl_( detail::make_variant_impl<Ts...>() )
            {}

            template<typename Val>
            YTL_CONSTEXPR variant( Val const& v )
                : impl_( detail::make_variant_impl<Ts...>( v, find_type_index<Val, Ts...>() ) )
            {}

        public:
            YTL_CONSTEXPR auto which() const -> std::size_t
            {
                return impl_.which_;
            }

        private:
            template<size_t Index, typename Visitor>
            YTL_CONSTEXPR auto apply_visitor_impl( Visitor const& visitor ) const
                -> typename std::enable_if<
                        ( Index < tuple_type::element_num ),
                        typename Visitor::result_type
                   >::type
            {
                return ( Index == impl_.which_ )
                            ? visitor( get<Index>( impl_.value_ ) )
                            : apply_visitor_impl<Index+1>( visitor );
            }

            template<size_t Index, typename Visitor>
            YTL_CONSTEXPR auto apply_visitor_impl( Visitor const& ) const
                -> typename std::enable_if<
                        ( Index == tuple_type::element_num ),
                        typename Visitor::result_type
                   >::type
            {
                return true
                        ? throw std::range_error( "unexpected. variant iteration reached to limit." )
                        : *reinterpret_cast<typename Visitor::result_type*>(0);
            }

        public:
            template<typename Visitor>
            YTL_CONSTEXPR auto apply_visitor( Visitor const& visitor ) const
                -> typename Visitor::result_type
            {
                return apply_visitor_impl<0>( visitor );
            }

        private:
            detail::variant_impl<Ts...> impl_;
        };

        template<typename Visitor, typename Variant>
        inline YTL_CONSTEXPR auto apply_visitor( Visitor const& visitor, Variant const& var )
            -> typename Visitor::result_type
        {
            return var.apply_visitor( visitor );
        }

    } // namespace cu
} // namespace ytl

#endif /*YTL_BASE_CONSTEXPR_UTILITY_VARIANT_HPP*/

#endif /*!defined(YTL_OLD_IMPL)*/