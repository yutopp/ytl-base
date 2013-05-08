#include "../config.hpp"

#if !defined(YTL_OLD_IMPL)

#ifndef YTL_BASE_CONSTEXPR_UTILITY_INDEX_TUPLE_HPP
#define YTL_BASE_CONSTEXPR_UTILITY_INDEX_TUPLE_HPP

#include <type_traits>

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

    } // namespace cu
} // namespace ytl

#endif /*YTL_BASE_CONSTEXPR_UTILITY_INDEX_TUPLE_HPP*/

#endif /*!defined(YTL_OLD_IMPL)*/