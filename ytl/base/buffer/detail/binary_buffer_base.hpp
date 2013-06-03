#ifndef YTL_BASE_DETAIL_BINARY_BUFFER_BASE_HPP
#define YTL_BASE_DETAIL_BINARY_BUFFER_BASE_HPP

#include <cstddef>
#include <type_traits>

#include "../../types.hpp"

namespace ytl
{
    namespace detail
    {
        //
        struct binary_buffer_policy
        {
            typedef byte_t                          value_type;
            typedef value_type&                     reference;
            typedef value_type const&               const_reference;
            typedef value_type*                     pointer;
            typedef value_type const*               const_pointer;

            typedef std::size_t                     size_type;
            typedef std::ptrdiff_t                  difference_type;
        };




        //
        template<
            template<typename Value, template<typename> class Allocator> class ContainerTraits
        >
        struct data_member_traits
        {
            template<typename T>
            static auto data( T& container )
                -> decltype( container.data() )
            {
                return container.data();
            }

            template<typename T>
            static auto data( T const& container )
                -> decltype( container.data() )
            {
                return container.data();
            }
        };


        //
        template<typename Container>
        struct container_copy_traits
        {
            typedef Container           container_type;

            template<typename Iter>
            container_type copy( Container const& unused__, Iter const& begin, Iter const& end )
            {
                return container_type( begin, end );
            }
        };


        template<typename Container, typename T, typename Iter>
        inline auto copy( T const& val, Iter const& begin, Iter const& end )
            -> typename container_copy_traits<Container>::container_type
        {
            return container_copy_traits<Container>().copy( val, begin, end );
        }


        //
        template<typename Container, typename MemberTraits>
        struct pointer_type_traits
        {
            typedef decltype( MemberTraits::data( std::declval<Container>() ) )         pointer;
            typedef decltype( MemberTraits::data( std::declval<Container const>() ) )   const_pointer;
        };


        //
        template<typename>
        struct unused_allocator {};


        // Tags
        struct fixed_tag {};
        struct resizable_tag {};
        struct readonly_tag {};


        // for CRTP...
        template<
            typename Derived,
            template<typename Value> class Allocator,
            template<
                typename Value,
                template<typename> class Acc
            > class ContainerImpl,
            typename BufferLevel
        >
        class binary_buffer_base;


        //
        template<typename Buffer>
        struct is_changable
            : std::true_type
        {};

        template<
            typename Derived,
            template<typename Value> class Allocator,
            template<
                typename Value,
                template<typename> class Acc
            > class ContainerImpl
        >
        struct is_changable<binary_buffer_base<Derived, Allocator, ContainerImpl, readonly_tag>>
            : std::false_type
        {};


        // Speciarized
        template<
            typename Derived,
            template<typename Value> class Allocator,
            template<
                typename Value,
                template<typename> class Acc
            > class ContainerImpl
        >
        class binary_buffer_base<Derived, Allocator, ContainerImpl, fixed_tag>
        {
        public:
            typedef Derived                                                             derived_type;

            typedef binary_buffer_policy::value_type                                    value_type;
            typedef Allocator<value_type>                                               allocator_type;
            typedef typename ContainerImpl<value_type, Allocator>::type                 wrapped_container_type;

        private:
            typedef data_member_traits<ContainerImpl>                                   data_function_traits;
            typedef pointer_type_traits<wrapped_container_type, data_function_traits>   data_pointer_type_traits;

        public:
            typedef typename wrapped_container_type::iterator                           iterator;
            typedef typename wrapped_container_type::const_iterator                     const_iterator;
            typedef typename wrapped_container_type::reference                          reference;
            typedef typename wrapped_container_type::difference_type                    difference_type;
            typedef typename wrapped_container_type::size_type                          size_type;

            typedef typename data_pointer_type_traits::pointer                          pointer;
            typedef typename data_pointer_type_traits::const_pointer                    const_pointer;

        // accessor(require: dereived class[has .get()])
        public:
            inline wrapped_container_type& operator*()
            {
                return reinterpret_cast<derived_type&>( *this ).get();
            }

            inline wrapped_container_type const& operator*() const
            {
                return reinterpret_cast<derived_type const&>( *this ).get();
            }

            inline wrapped_container_type* operator->()
            {
                return std::addressof( *(*this) );
            }

            inline wrapped_container_type const* operator->() const
            {
                return std::addressof( *(*this) );
            }

        // basic method(require: container impl[has .begin()|.end()|.size()|,empty()])
        public:
            inline iterator begin()
            {
                return (*this)->begin();
            }

            inline const_iterator begin() const
            {
                return (*this)->begin();
            }

            inline iterator end()
            {
                return (*this)->end();
            }

            inline const_iterator end() const
            {
                return (*this)->end();
            }

            inline size_type size() const
            {
                return (*this)->size();
            }

            inline bool empty() const
            {
                return (*this)->empty();
            }

        // acsess method(require: container impl[has .data()|.at()|.operator[]()])
        public:
            inline pointer data()
            {
                return data_function_traits::data( *(*this) );
            }

            inline const_pointer data() const
            {
                return data_function_traits::data( *(*this) );
            }

            inline value_type& operator[]( size_type const index )
            {
                return (*this)->operator[]( index );
            }

            inline value_type const& operator[]( size_type const index ) const
            {
                return (*this)->operator[]( index );
            }
        };





        template<
            typename Derived,
            template<typename Value> class Allocator,
            template<
                typename Value,
                template<typename> class Acc
            > class ContainerImpl
        >
        class binary_buffer_base<Derived, Allocator, ContainerImpl, readonly_tag>
        {
        public:
            typedef Derived                                                             derived_type;

            typedef binary_buffer_policy::value_type                                    value_type;
            typedef Allocator<value_type>                                               allocator_type;
            typedef typename ContainerImpl<value_type, Allocator>::type                 wrapped_container_type;

        private:
            typedef data_member_traits<ContainerImpl>                                   data_function_traits;
            typedef pointer_type_traits<wrapped_container_type, data_function_traits>   data_pointer_type_traits;

        public:
            typedef typename wrapped_container_type::const_iterator                     iterator;
            typedef typename wrapped_container_type::const_iterator                     const_iterator;
            //typedef typename wrapped_container_type::reference                          reference;
            typedef typename wrapped_container_type::difference_type                    difference_type;
            typedef typename wrapped_container_type::size_type                          size_type;

            typedef typename data_pointer_type_traits::const_pointer                    pointer;
            typedef typename data_pointer_type_traits::const_pointer                    const_pointer;

        // accessor(require: dereived class[has .get()])
        public:
            inline wrapped_container_type const& operator*() const
            {
                return reinterpret_cast<derived_type const&>( *this ).get();
            }

            inline wrapped_container_type const* operator->() const
            {
                return std::addressof( *(*this) );
            }

        // basic method(require: container impl[has .begin()|.end()|.size()|,empty()])
        public:
            inline const_iterator begin() const
            {
                return (*this)->begin();
            }

            inline const_iterator end() const
            {
                return (*this)->end();
            }

            inline size_type size() const
            {
                return (*this)->size();
            }

            inline bool empty() const
            {
                return (*this)->empty();
            }

        // acsess method(require: container impl[has .data()|.at()|.operator[]()])
        public:
            inline const_pointer data() const
            {
                return data_function_traits::data( *(*this) );
            }

            inline value_type const& operator[]( size_type const index ) const
            {
                return (*this)->operator[]( index );
            }
        };




        template<
            typename Derived,
            template<typename Value> class Allocator,
            template<
                typename Value,
                template<typename> class Acc
            > class ContainerImpl
        >
        class binary_buffer_base<Derived, Allocator, ContainerImpl, resizable_tag>
        {
        public:
            typedef Derived                                                             derived_type;

            typedef binary_buffer_policy::value_type                                    value_type;
            typedef Allocator<value_type>                                               allocator_type;
            typedef typename ContainerImpl<value_type, Allocator>::type                 wrapped_container_type;

        private:
            typedef data_member_traits<ContainerImpl>                                   data_function_traits;
            typedef pointer_type_traits<wrapped_container_type, data_function_traits>   data_pointer_type_traits;

        public:
            typedef typename wrapped_container_type::iterator                           iterator;
            typedef typename wrapped_container_type::const_iterator                     const_iterator;
            typedef typename wrapped_container_type::reference                          reference;
            typedef typename wrapped_container_type::difference_type                    difference_type;
            typedef typename wrapped_container_type::size_type                          size_type;

            typedef typename data_pointer_type_traits::pointer                          pointer;
            typedef typename data_pointer_type_traits::const_pointer                    const_pointer;

        // accessor(require: dereived class[has .get()])
        public:
            inline wrapped_container_type& operator*()
            {
                return reinterpret_cast<derived_type&>( *this ).get();
            }

            inline wrapped_container_type const& operator*() const
            {
                return reinterpret_cast<derived_type const&>( *this ).get();
            }

            inline wrapped_container_type* operator->()
            {
                return std::addressof( *(*this) );
            }

            inline wrapped_container_type const* operator->() const
            {
                return std::addressof( *(*this) );
            }

        // basic method(require: container impl[has .begin()|.end()|.size()|,empty()])
        public:
            inline iterator begin()
            {
                return (*this)->begin();
            }

            inline const_iterator begin() const
            {
                return (*this)->begin();
            }

            inline iterator end()
            {
                return (*this)->end();
            }

            inline const_iterator end() const
            {
                return (*this)->end();
            }

            inline size_type size() const
            {
                return (*this)->size();
            }

            inline bool empty() const
            {
                return (*this)->empty();
            }

        // acsess method(require: container impl[has .data()|.at()|.operator[]()])
        public:
            inline pointer data()
            {
                return data_function_traits::data( *(*this) );
            }

            inline const_pointer data() const
            {
                return data_function_traits::data( *(*this) );
            }

            inline value_type& operator[]( size_type const index )
            {
                return (*this)->operator[]( index );
            }

            inline value_type const& operator[]( size_type const index ) const
            {
                return (*this)->operator[]( index );
            }

        // resize method(require: container impl[has .resize()|.push_back()])
        public:
            inline void resize( size_type const size )
            {
                (*this)->resize( size );
            }

            inline void push_back( value_type const& value )
            {
                (*this)->push_back( value );
            }
        };

        } // namespace detail

        // ----------------------------------------------------------------------------------------------------
        template<
            typename LhsDerived,
            template<typename Value> class LhsAllocator,
            template<typename Value, template<typename> class Acc> class LhsContainerImpl,
            typename LhsBufferLevel,
            typename RhsDerived,
            template<typename Value> class RhsAllocator,
            template<typename Value, template<typename> class Acc> class RhsContainerImpl,
            typename RhsBufferLevel
        >
        inline auto operator<<(
                        detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>& lhs,
                        detail::binary_buffer_base<RhsDerived, RhsAllocator, RhsContainerImpl, RhsBufferLevel> const& rhs
                        ) -> typename std::enable_if<
                                detail::is_changable<detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>>::value,
                                typename detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>::derived_type&
                             >::type
        {
            // call container method directly
            lhs->insert( lhs.end(), rhs.begin(), rhs.end() );

            return static_cast<
                        typename detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>::derived_type&
                   >( lhs );
        }

        template<
            typename LhsDerived,
            template<typename Value> class LhsAllocator,
            template<typename Value, template<typename> class Acc> class LhsContainerImpl,
            typename LhsBufferLevel,
            std::size_t N
        >
        inline auto operator<<(
                        detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>& lhs,
                        byte_t const (&rhs)[N]
                        ) -> typename std::enable_if<
                                detail::is_changable<detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>>::value,
                                typename detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>::derived_type&
                             >::type
        {
            // call container method directly
            lhs->insert( lhs.end(), rhs, rhs + N );

            return static_cast<
                        typename detail::binary_buffer_base<LhsDerived, LhsAllocator, LhsContainerImpl, LhsBufferLevel>::derived_type&
                   >( lhs );
        }
        // ----------------------------------------------------------------------------------------------------

    
} // namespace ytl

#endif /*YTL_BASE_DETAIL_BINARY_BUFFER_BASE_HPP*/
