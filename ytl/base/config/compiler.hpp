#ifndef YTL_BASE_CONFIG_COMPILER_HPP
#define YTL_BASE_CONFIG_COMPILER_HPP

#include <boost/config.hpp>

#if defined( _MSC_VER )
# define YTL_C_MSVC

#elif defined( __GNUC__ )
# define YTL_C_GCC

#elif defined( __clang__ )
# define YTL_C_CLANG

#else
# define YTL_C_OTHER

#endif


// For constexpr
#if !defined(BOOST_NO_CONSTEXPR) && !defined(YTL_NO_USE_CONSTEXPR)
# define YTL_HAS_CONSTEXPR
# define YTL_CONSTEXPR constexpr
#else
# define YTL_CONSTEXPR
#endif /*!defined(BOOST_NO_CONSTEXPR) || !defined(YTL_NO_USE_CONSTEXPR)*/


//
#if defined(BOOST_NO_CONSTEXPR) || defined(BOOST_NO_UNIFIED_INITIALIZATION_SYNTAX) || defined(BOOST_NO_VARIADIC_TEMPLATES)
# define YTL_OLD_IMPL
#endif /*defined(BOOST_NO_CONSTEXPR) || defined(BOOST_NO_UNIFIED_INITIALIZATION_SYNTAX) || defined(BOOST_NO_VARIADIC_TEMPLATES)*/

#endif /*YTL_BASE_CONFIG_COMPILER_HPP*/
