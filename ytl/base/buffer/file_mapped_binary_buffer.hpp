#ifndef YTL_FILE_MAPPED_BINARY_BUFFER_HPP
#define YTL_FILE_MAPPED_BINARY_BUFFER_HPP

#include <utility>

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/noncopyable.hpp>

#include "detail/binary_buffer_base.hpp"
#include "detail/binary_range_traits.hpp"

namespace ytl
{
    // file mapped binary buffer
    class file_mapped_binary_buffer
        : public detail::binary_buffer_base<
                    file_mapped_binary_buffer,
                    detail::unused_allocator,
                    detail::binary_range_container,
                    detail::readonly_tag
                 >
        , private boost::noncopyable
    {
    public:
        typedef file_mapped_binary_buffer               self_type;
        typedef detail::binary_buffer_base<
                    file_mapped_binary_buffer,
                    detail::unused_allocator,
                    detail::binary_range_container,
                    detail::readonly_tag
                >                                       base_type;

        typedef self_type::wrapped_container_type       wrapped_container_type;
        typedef self_type::value_type                   value_type;

    public:
        file_mapped_binary_buffer( char const* file_path )
            : memmap_( file_path, boost::interprocess::read_only )
            , view_( memmap_, boost::interprocess::read_only )
            , range_(
                    static_cast<value_type*>( view_.get_address() ),
                    static_cast<value_type*>( view_.get_address() ) + view_.get_size()
                    )
        {}

    public:
        file_mapped_binary_buffer( file_mapped_binary_buffer&& rhs )
            : memmap_( std::move( rhs.memmap_ ) )
            , view_( std::move( rhs.view_ ) )
            , range_( std::move( rhs.range_ ) )
        {}

    public:
        wrapped_container_type& get()
        {
            return range_;
        }
    
        wrapped_container_type const& get() const
        {
            return range_;
        }

    private:
        boost::interprocess::file_mapping memmap_;
        boost::interprocess::mapped_region view_;

        wrapped_container_type range_;
    };
} // namespace ytl

#endif /*YTL_FILE_MAPPED_BINARY_BUFFER_HPP*/
