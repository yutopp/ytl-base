#ifndef YTL_BASE_TYPES_HPP
#define YTL_BASE_TYPES_HPP

#include <cstddef>
#include <boost/cstdint.hpp>

namespace ytl
{
    typedef	boost::int8_t           int8_t;
    typedef	boost::int16_t          int16_t;
    typedef	boost::int32_t          int32_t;
    typedef boost::int64_t          int64_t;

    typedef int16_t                 short_t;
    
    typedef boost::uint8_t          uint8_t;
    typedef boost::uint16_t         uint16_t;
    typedef boost::uint32_t         uint32_t;
    typedef boost::uint64_t         uint64_t;

    typedef uint64_t                ulonglong_t;
    
    typedef uint8_t                 byte_t;
    typedef uint16_t                word_t;
    typedef	uint32_t                dword_t;
    typedef	uint64_t                qword_t;

/*	typedef boost::uint_least8_t	byte_t;
	typedef boost::uint_least16_t	word_t;
	typedef	boost::uint_least32_t	dword_t;*/

} // namespace ytl

#endif /*YTL_BASE_TYPES_HPP*/