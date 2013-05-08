#ifndef YTL_BASE_HELPER_LOAD_BINARY_FILE_HPP
#define YTL_BASE_HELPER_LOAD_BINARY_FILE_HPP

#include "../buffer/binary_buffer.hpp"
#include "load_file.hpp"

namespace ytl
{
    // type specified
    template<typename CharT>
    inline auto load_binary_file( CharT const* const filename ) -> binary_buffer
    {
        return load_file<binary_buffer>( filename );
    }

    template<typename CharT>
    inline auto load_binary_file( std::basic_string<CharT> const& filename ) -> binary_buffer
    {
        return load_binary_file<binary_buffer>( filename.c_str() );
    }

} // namespace ytl

#endif /*YTL_BASE_HELPER_LOAD_BINARY_FILE_HPP*/
