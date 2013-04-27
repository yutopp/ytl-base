#ifndef YTL_UTILITY_MAP_BINARY_FILE_HPP
#define YTL_UTILITY_MAP_BINARY_FILE_HPP

#include <ytl/buffer/file_mapped_binary_buffer.hpp>

namespace ytl
{
    template<typename CharT>
    inline file_mapped_binary_buffer map_binary_file( CharT const* const filename )
    {
        return file_mapped_binary_buffer( filename );
    }

    template<typename CharT>
    inline file_mapped_binary_buffer map_binary_file( std::basic_string<CharT> const& filename )
    {
        return file_mapped_binary_buffer( filename.c_str() );
    }

} // namespace ytl

#endif /*YTL_UTILITY_MAP_BINARY_FILE_HPP*/