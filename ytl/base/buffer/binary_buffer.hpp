#ifndef YTL_BASE_BUFFER_BINARY_BUFFER_HPP
#define YTL_BASE_BUFFER_BINARY_BUFFER_HPP

#include <vector>

#include "../helper/alignment.hpp"

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
        : public detail::binary_buffer_base<
                    basic_binary_buffer<Allocator>,
                    Allocator,
                    detail::binary_buffer_container,
                    detail::resizable_tag
                 >
    {
    public:
        typedef basic_binary_buffer                             self_type;
        typedef detail::binary_buffer_base<
                    basic_binary_buffer,
                    Allocator,
                    detail::binary_buffer_container,
                    detail::resizable_tag
                >                                               base_type;

        typedef typename base_type::wrapped_container_type      wrapped_container_type;
        typedef typename base_type::size_type                   size_type;
        typedef typename base_type::value_type                  value_type;

    public:
        basic_binary_buffer()
        {}

        basic_binary_buffer( size_type const size )
            : buffer_( size )
        {}

        template<typename IterT>
        basic_binary_buffer( IterT const& begin, IterT const& end )
            : buffer_( begin, end )
        {}

    public:
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

    private:
        wrapped_container_type buffer_;
    };

    //
    typedef basic_binary_buffer<std::allocator>            binary_buffer;

} // namespace ytl

#endif /*YTL_BASE_BUFFER_BINARY_BUFFER_HPP*/