#ifndef YTL_BINARY_BUFFER_STL_HPP
#define YTL_BINARY_BUFFER_STL_HPP

#include <ostream>
#include <iomanip>
#include <string>
#include <type_traits>

#include "detail/binary_buffer_base.hpp"

namespace ytl
{
    // insert string with null terminate
    template<
        typename LhsDerived,
        template<typename Value> class LhsAllocator,
        template<typename Value, template<typename> class Acc> class LhsContainerImpl,
        typename LhsBufferLevel
    >
    inline auto operator<<(
                    detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>& lhs,
                    std::string const& rhs
                    ) -> typename std::enable_if<
                            detail::is_changable<detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>>::value,
                            typename detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>::derived_type&
                         >::type
    {
        lhs->insert( lhs.end(), rhs.begin(), rhs.end() );
        lhs->push_back( 0x00 );  // Null terminate

        return static_cast<
                    typename detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>::derived_type&
               >( lhs );
    }


    // output
    template<
        typename Derived,
        template<typename Value> class Allocator,
        template<typename Value, template<typename> class Acc> class ContainerImpl,
        typename BufferLevel
    >
    inline auto operator<<=(
                    std::ostream& ofs,
                    detail::binary_buffer_base<Derived, Allocator, ContainerImpl, BufferLevel> const& buffer
                    ) -> std::ostream&
    {
        ofs.write( reinterpret_cast<char const*>( &buffer.data()[0] ), buffer.size() );

        return ofs;
    }

    // debug output
    template<
        typename Derived,
        template<typename Value> class Allocator,
        template<typename Value, template<typename> class Acc> class ContainerImpl,
        typename BufferLevel
    >
    inline auto operator<<(
                    std::ostream& os,
                    detail::binary_buffer_base<Derived, Allocator, ContainerImpl, BufferLevel> const& buffer
                    ) -> std::ostream&
    {
        auto const manip = os.flags();
        
        os << "[ " << std::hex;
        for( std::size_t i=0; i<buffer.size(); ++i ) {
            os << "'0x" << std::setfill('0') << std::setw( 2 ) << static_cast<int>( buffer[i] ) << "' ";
        }
        os.setf( manip );
        os << "]";

        return os;
    }
} // namespace ytl

#endif /*YTL_BINARY_BUFFER_STL_HPP*/
