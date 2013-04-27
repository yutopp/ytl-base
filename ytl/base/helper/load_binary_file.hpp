#ifndef YTL_UTILITY_LOAD_BINARY_FILE_HPP
#define YTL_UTILITY_LOAD_BINARY_FILE_HPP

#include <ytl/buffer/binary_buffer.hpp>

#include "load_file.hpp"

namespace ytl
{
    // type specified
    template<typename CharT>
    inline binary_buffer load_binary_file( CharT const* const filename )
    {
        return load_file<binary_buffer>( filename );
    }

    template<typename CharT>
    inline binary_buffer load_binary_file( std::basic_string<CharT> const& filename )
    {
        return load_binary_file<binary_buffer>( filename.c_str() );
    }

} // namespace ytl

#endif /*YTL_UTILITY_LOAD_BINARY_FILE_HPP*/
