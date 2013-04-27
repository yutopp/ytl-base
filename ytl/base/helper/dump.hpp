#ifndef YTL_UTILITY_DUMP_HPP
#define YTL_UTILITY_DUMP_HPP

#include <cstdio>
#include <cstddef>

#include <iostream>
#include <string>

#include <boost/optional.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>

#include <ytl/config.hpp>

namespace ytl
{
    namespace detail
    {
        template<std::size_t N, typename Buffer>
        void dumpbin_impl(
            Buffer const& bin,
            std::size_t offset,
            boost::optional<std::size_t> opt_size
            )
        {
            static std::size_t const width = 16;    // column

            if ( offset >= bin.size() ) {
                return;
            }

            std::size_t const size = [&]() -> std::size_t
                {
                    if ( !opt_size ) {
                        return bin.size();
                    } else if ( *opt_size > bin.size() + offset ) {
                        return bin.size() + offset;
                    } else {
                        return *opt_size;
                    }
                }();

            std::string const padding( N + 3, ' ' ), left_format( "%0" + boost::lexical_cast<std::string>( N ) + "X | " );

            std::cout << padding;
            for( std::size_t i=0; i<width; ++i ) {
                std::cout << boost::format( "%1$02X " ) % i;
            }
            std::cout << std::endl;

			std::printf( padding.c_str() );
			for( std::size_t i=0; i<width; ++i ) {
				std::printf( "-- " );
			}
			std::printf( "  " );
			for( std::size_t i=0; i<width/2; ++i ) {
				std::printf( "-+" );
			}
			std::printf( "\n" );

			auto it = bin.begin() + offset;
			std::size_t line = 0;
			do {
				// address
				std::printf( left_format.c_str(), offset + line * width );

				// binary
				[&, it]() mutable {
					for( auto i=0; i<width; ++i ) {
						if ( it < bin.end() ) {
							std::printf( "%02X ", static_cast<unsigned char>( *it ) );
							++it;
						} else {
							std::printf( "   " );
						}
					}
				}();
				std::printf( "| " );

				// ascii
				[&, it]() mutable {
					for( auto i=0; i<width; ++i ) {
						if ( it < bin.end() ) {
							std::printf( "%c", ( *it < 0x20 || *it > 0x7e ) ? '.' : *it );
							++it;
						} else {
							std::printf( " " );
						}
					}
				}();
				std::printf( "\n" );

				for( auto i=0; i<width; ++i ) {
					if ( it < bin.end() ) {
						++it;
					}
				}
				++line;
            } while( line < aligned_size( size, width ) / width );
		}

	} // namespace detail


    template<typename Buffer>
    inline void dumpbin32(
        Buffer const& bin,
        std::size_t const offset = 0,
        boost::optional<std::size_t> size = boost::none
        )
    {
        detail::dumpbin_impl<8>( bin, offset, size );
    }

    template<typename Buffer>
    inline void dumpbin64(
        Buffer const& bin,
        std::size_t const offset = 0,
        boost::optional<std::size_t> size = boost::none
        )
    {
        detail::dumpbin_impl<16>( bin, offset, size );
    }

} // namespace ytl

#endif /*YTL_UTILITY_DUMP_HPP*/
