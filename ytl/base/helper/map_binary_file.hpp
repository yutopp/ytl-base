#ifndef YTL_BASE_HELPER_MAP_BINARY_FILE_HPP
#define YTL_BASE_HELPER_MAP_BINARY_FILE_HPP

#include "../buffer/file_mapped_binary_buffer.hpp"

namespace ytl
{
    template<typename CharT>
    inline auto map_binary_file( CharT const* const filename ) -> file_mapped_binary_buffer
    {
        return file_mapped_binary_buffer( filename );
    }

    template<typename CharT>
    inline auto map_binary_file( std::basic_string<CharT> const& filename ) -> file_mapped_binary_buffer
    {
        return file_mapped_binary_buffer( filename.c_str() );
    }

} // namespace ytl

#endif /*YTL_BASE_HELPER_MAP_BINARY_FILE_HPP*/