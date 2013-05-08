#ifndef YTL_BASE_HELPER_ALIGNMENT_HPP
#define YTL_BASE_HELPER_ALIGNMENT_HPP

#include "../config.hpp"

#if defined( YTL_C_MSVC )

#define YTL_ALIGN( N ) __declspec( align( N ) )

#elif defined( YTL_C_GCC )

#define YTL_ALIGN( N ) __attribute__ ((aligned( N )))

#else

#error Not supported...

#endif

namespace ytl
{
    inline YTL_CONSTEXPR std::size_t padding_size( std::size_t const size, std::size_t alignment )
    {
        return alignment - size % alignment;
    }

    inline YTL_CONSTEXPR std::size_t aligned_size( std::size_t const size, std::size_t alignment )
    {
        return size + padding_size( size, alignment );
    }
}

#endif /*YTL_BASE_HELPER_ALIGNMENT_HPP*/