#ifndef YTL_BINARY_BUFFER_IMMUTABLE_PACK_HPP
#define YTL_BINARY_BUFFER_IMMUTABLE_PACK_HPP

#include <memory>
#include <type_traits>

#include <boost/noncopyable.hpp>

#include "../helper/guard_macros.hpp"
#include "detail/binary_buffer_base.hpp"


namespace ytl
{
    class binary_buffer_immutable_pack
    {
    public:
        typedef detail::binary_buffer_policy::value_type            value_type;
        typedef detail::binary_buffer_policy::const_pointer         const_pointer;
        typedef detail::binary_buffer_policy::size_type             size_type;

    private:
        class holder_base
            : private boost::noncopyable
        {
        public:
            virtual ~holder_base() {}

            virtual const_pointer data() const =0;
            virtual const_pointer begin() const =0;
            virtual const_pointer end() const =0;
            virtual size_type size() const =0;
        };

        template<typename Buffer>
        class holder
            : public holder_base
        {
            YTL_REQUIRE_BINARY_BUFFER( Buffer )

            typedef typename std::remove_reference<Buffer>::type    buffer_type;

        public:
            holder( buffer_type buffer )
                : buffer_( std::move( buffer ) )
            {}

            const_pointer data() const
            {
                return buffer_.data();
            }

            const_pointer begin() const
            {
                return buffer_.begin();
            }

            const_pointer end() const
            {
                return buffer_.end();
            }

            size_type size() const
            {
                return buffer_.size();
            }

        public:
            buffer_type buffer_;
        };

    private:
        typedef std::shared_ptr<holder_base>                        holder_type;

    // copy/move ctor
    public:
        binary_buffer_immutable_pack(
            binary_buffer_immutable_pack const& rhs
            )
            : holder_( rhs.holder_ )
        {}

        binary_buffer_immutable_pack(
            binary_buffer_immutable_pack&& rhs
            )
            : holder_( std::move( rhs.holder_ ) )
        {}

    // construct from other buffer
    // 
    public:
        // for rvalue
        template<typename Buffer>
        binary_buffer_immutable_pack(
            Buffer&& buffer,
            typename std::enable_if<
                std::is_rvalue_reference<Buffer&&>::value
                && !std::is_same<typename std::decay<Buffer>::type, binary_buffer_immutable_pack>::value
            >::type* =0
            )
            : holder_( std::make_shared<holder<Buffer>>( std::move( buffer ) ) )
        {}

        // for lvalue(do copy)
        template<typename Buffer>
        binary_buffer_immutable_pack(
            Buffer&& buffer,
            typename std::enable_if<
                !std::is_rvalue_reference<Buffer&&>::value
                && !std::is_same<typename std::decay<Buffer>::type, binary_buffer_immutable_pack>::value
            >::type* =0
            )
            : holder_( std::make_shared<holder<Buffer>>( buffer ) )
        {}

        // unique_ptr
        template<typename Buffer>
        binary_buffer_immutable_pack(
            std::unique_ptr<Buffer> buffer/*,
            typename std::enable_if<!std::is_reference<Buffer>::value>::type* =0        // only value contain pointer */
            )
            : holder_( std::make_shared<holder<Buffer>>( std::move( *buffer ) ) )
        {}

    public:
        template<typename T>
        auto operator=( binary_buffer_immutable_pack const& rhs ) -> binary_buffer_immutable_pack&
        {
            if ( this != &rhs ) {
                binary_buffer_immutable_pack t( rhs );
                t.swap( *this );
            }

            return *this;
        }

        template<typename T>
        auto operator=( binary_buffer_immutable_pack&& rhs ) -> binary_buffer_immutable_pack&
        {
            if ( this != &rhs ) {
                binary_buffer_immutable_pack t( std::move( rhs ) );
                t.swap( *this );
            }

            return *this;
        }

    public:
        const_pointer data() const
        {
            return holder_->data();
        }

        const_pointer begin() const
        {
            return holder_->begin();
        }

        const_pointer end() const
        {
            return holder_->end();
        }

        size_type size() const
        {
            return holder_->size();
        }

        void swap( binary_buffer_immutable_pack& rhs )
        {
            using std::swap;

            swap( holder_, rhs.holder_ );
        }

    private:
        holder_type holder_;
    };


    template<typename Buffer>
    inline auto to_immutable_pack( Buffer&& buf ) -> binary_buffer_immutable_pack
    {
        return binary_buffer_immutable_pack( std::forward<Buffer>( buf ) );
    }


} // namespace ytl

#endif /*YTL_BINARY_BUFFER_IMMUTABLE_PACK_HPP*/
