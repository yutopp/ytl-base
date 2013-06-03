#ifndef YTL_BASE_BUFFER_SHORT_BUFFER_HPP
#define YTL_BASE_BUFFER_SHORT_BUFFER_HPP

#include <iostream>
#include <iomanip>

#include "detail/short_buffer_impl.hpp"

namespace ytl
{
    namespace detail
    {
        // debug
        template<typename SizeType, SizeType N>
        std::ostream& operator<<( std::ostream& os, short_buffer<SizeType, N> const& b )
        {
            auto const manip = os.flags();
            os << "[ " << std::hex;
            for( std::size_t i=0; i<b.size(); ++i ) {
                os << "'0x" << std::setfill('0') << std::setw( 2 ) << static_cast<int>( b[i] ) << "' ";
            }
            os.setf( manip );
            os << "]";
            return os;
        }
    } // namespace detail

    // make_short_buffer
#if !defined(YTL_OLD_IMPL)

    template<typename ...T>
    YTL_CONSTEXPR auto make_short_buffer( T&&... xs ) -> detail::short_buffer<typename boost::uint_value_t<sizeof...(T)>::least, sizeof...(T)>
    {
        using namespace detail;

        return short_buffer<typename boost::uint_value_t<sizeof...(T)>::least, sizeof...(T)>( short_buffer_construct, std::forward<T>( xs )... );
    }

#else

# include <boost/preprocessor/repetition/enum_params.hpp>
# include <boost/preprocessor/repetition/enum_binary_params.hpp>
# include <boost/preprocessor/repetition/repeat_from_to.hpp>

# define FORWARD_P(z, n, unused) std::forward<T##n>( p##n )
# define GEN_B(z, n, unused) \
    template<BOOST_PP_ENUM_PARAMS(n, typename T)> \
    auto make_short_buffer( BOOST_PP_ENUM_BINARY_PARAMS(n, T, && p) ) -> detail::short_buffer<typename boost::uint_value_t<n>::least, n> \
    { \
        return detail::short_buffer<typename boost::uint_value_t<n>::least, n>( detail::short_buffer_construct, BOOST_PP_ENUM(n, FORWARD_P, ) ); \
    }

    auto make_short_buffer() -> detail::short_buffer<typename boost::uint_value_t<0>::least, 0>
    {
        return detail::short_buffer<typename boost::uint_value_t<0>::least, 0>( detail::short_buffer_construct );
    }
    BOOST_PP_REPEAT_FROM_TO(1, 64/*temporary*/, GEN_B, )

# undef FORWARD_P
# undef GEN_B

#endif/*!defined(YTL_OLD_IMPL)*/

} // namespace ytl

#endif /*YTL_BASE_BUFFER_SHORT_BUFFER_HPP*/