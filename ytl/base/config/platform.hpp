#ifndef YTL_BASE_CONFIG_PLATFORM_HPP
#define YTL_BASE_CONFIG_PLATFORM_HPP

#include <boost/config.hpp>
#include <boost/detail/endian.hpp>

#if defined(BOOST_WINDOWS)
# define YTL_WINDOWS
#endif /*defined(BOOST_WINDOWS)*/

#if defined(BOOST_LITTLE_ENDIAN)
# define YTL_LITTLE_ENDIAN
#elif defined(BOOST_BIG_ENDIAN)
# define YTL_BIG_ENDIAN
#else
# error
#endif /*defined(BOOST_LITTLE_ENDIAN)*/


#endif /*YTL_BASE_CONFIG_PLATFORM_HPP*/
