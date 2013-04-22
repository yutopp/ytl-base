#if !defined(YTL_OLD_IMPL)

#ifndef YTL_BASE_CONSTEXPR_UTILITY_INDEX_TUPLE_HPP
#define YTL_BASE_CONSTEXPR_UTILITY_INDEX_TUPLE_HPP

#include <type_traits>

#include "../config.hpp"


namespace ytl
{
    namespace cu
    {
        template<typename NumType, NumType... Indexes>
        struct index_tuple {};

        namespace detail
        {
            template<typename NumType, std::size_t Remain>
            struct make_index_tuple_impl
            {
                template<NumType Next, NumType End, NumType Step, NumType... Indexes>
                YTL_CONSTEXPR auto create() const
                    -> decltype( make_index_tuple_impl<NumType, Remain-1>().template create<Next + Step, End, Step, Indexes..., Next>() )
                {
                    return make_index_tuple_impl<NumType, Remain-1>().template create<Next + Step, End, Step, Indexes..., Next>();
                }
            };

            template<typename NumType>
            struct make_index_tuple_impl<NumType, 0>
            {
                template<NumType Next, NumType End, NumType Step, NumType... Indexes>
                YTL_CONSTEXPR auto create() const
                    -> index_tuple<NumType, Indexes...>
                {
                     return index_tuple<NumType, Indexes...>();
                }
            };
        } // namespace detail

        // make_index_list
        template<typename NumType, NumType Begin, NumType End, NumType Step = 1>
        inline YTL_CONSTEXPR auto make_index_tuple()
            -> decltype( detail::make_index_tuple_impl<NumType, (Begin < End) ? ( ( ( End - Begin ) + ( ( End - Begin ) % Step ) ) / Step ) : 0>().template create<Begin, End, Step>() )
        {
            return detail::make_index_tuple_impl<NumType, (Begin < End) ? ( ( ( End - Begin ) + ( ( End - Begin ) % Step ) ) / Step ) : 0>().template create<Begin, End, Step>();
        }

/*
    {
        static_assert( std::is_same<decltype( ytl::cu::make_index_list<0, 0>() ), ytl::cu::index_list<>>::value, "" );
        static_assert( std::is_same<decltype( ytl::cu::make_index_list<3, 0>() ), ytl::cu::index_list<>>::value, "" );
        static_assert( std::is_same<decltype( ytl::cu::make_index_list<0, 5, 1>() ), ytl::cu::index_list<0, 1, 2, 3, 4>>::value, "" );
        static_assert( std::is_same<decltype( ytl::cu::make_index_list<0, 9, 2>() ), ytl::cu::index_list<0, 2, 4, 6, 8>>::value, "" );
        //static_assert( std::is_same<decltype( ytl::cu::make_irange<0, 5, 1>() ), ytl::cu::irange<0, 1, 2, 3, 4> >::value, "" );
//        static_assert( ytl::cu::get<1>( ytl::cu::detail::type_indexer<double>().prove<bool, int, double>( 0 ) ) == 2, "" );
//
//        static_assert( ytl::cu::get<0>( ytl::cu::detail::type_indexer<char>().prove<bool, int, double>( 0 ) ) == false, "" );
    }
*/


    } // namespace cu
} // namespace ytl

#endif /*YTL_BASE_CONSTEXPR_UTILITY_INDEX_TUPLE_HPP*/

#endif /*!defined(YTL_OLD_IMPL)*/