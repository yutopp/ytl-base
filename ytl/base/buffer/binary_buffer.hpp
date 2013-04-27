#ifndef YTL_BINARY_BUFFER_HPP
#define YTL_BINARY_BUFFER_HPP

#include <vector>

#include <ytl/utility/alignment.hpp>

#include "detail/binary_buffer_base.hpp"

namespace ytl
{
    namespace detail
    {
        template<typename Value, template<typename> class Allocator>
        struct binary_buffer_container
        {
            typedef std::vector<Value, Allocator<Value>>        type;
        };

    } // namespace detail


    // binary buffer
    template<template <typename> class Allocator>
    class basic_binary_buffer
        : public detail::resizable_buffer_base<
                    basic_binary_buffer<Allocator>, Allocator,
                    detail::binary_buffer_container
                >
    {
    public:
        typedef basic_binary_buffer                             self_type;
        typedef typename self_type::base_type                   base_type;

        typedef typename base_type::wrapped_container_type      wrapped_container_type;

        typedef typename base_type::size_type                   size_type;
        typedef typename base_type::value_type                  value_type;

    public:
        basic_binary_buffer()
        {}

/*      binary_buffer( size_type const size )
            : buffer_( size )
        {}*/

/*      template<typename IterT>
        binary_buffer( IterT const& begin, IterT const& end )
            : buffer_( begin, end )
        {
//          std::cout << "basic_binary: iter ctor." << std::endl;
        }*/


        wrapped_container_type& get()
        {
            return buffer_;
        }

        wrapped_container_type const& get() const
        {
            return buffer_;
        }

        void swap( self_type& rhs )
        {
            using std::swap;

            swap( buffer_, rhs.buffer_ );
        }

    public:
        void padding( size_type padding, value_type v = 0 )
        {
            for( size_type i=0; i<padding; ++i ) {
                buffer_.emplace_back( v );
            }
        }

        void align( size_type alignment, value_type v = 0 )
        {
            padding( ytl::padding_size( buffer_.size(), alignment ), v );
        }

        template<typename T>
        void expand_raw_binary( T&& object )
        {
            binary_expand( std::forward<T>( object ) );
        }

        // duprecated...
        template<typename T>
        void binary_expand( T const& object )
        {
            auto const p
                = reinterpret_cast<value_type const*>( &object );
            std::copy( p, p + sizeof( T ), std::back_inserter( buffer_ ) );
        }

    private:
        wrapped_container_type buffer_;
    };


    //
    typedef basic_binary_buffer<std::allocator>            binary_buffer;

    //

} // namespace ytl

#endif /*YTL_BINARY_BUFFER_HPP*/
