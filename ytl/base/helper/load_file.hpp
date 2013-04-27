#ifndef YTL_UTILITY_LOAD_FILE_HPP
#define YTL_UTILITY_LOAD_FILE_HPP

#include <string>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <algorithm>

#include <ytl/config.hpp>

namespace ytl
{
    template<typename Buffer, typename CharT>
    void load_file( CharT const* const filename, Buffer& dst )
    {
        std::basic_ifstream<char> ifs( filename, std::ios_base::in | std::ios::binary );
        if ( !ifs )
            throw std::runtime_error( "File not found." );

        std::istreambuf_iterator<char> const begin( ifs ), end;
        std::copy( begin, end, std::back_inserter( dst ) );
    }

    template<typename Buffer, typename CharT>
    inline void load_file( std::basic_string<CharT> const& filename, Buffer& dst )
    {
        load_file( filename.c_str(), dst );
    }

    template<typename Buffer, typename CharT>
    Buffer load_file( CharT const* const filename )
    {
        Buffer buf;
        load_file( filename, buf );

        return buf;
    }

    template<typename Buffer, typename CharT>
    inline Buffer load_file( std::basic_string<CharT> const& filename )
    {
        return load_file<Buffer>( filename.c_str() );
    }

} // namespace ytl

#endif /*YTL_UTILITY_LOAD_FILE_HPP*/