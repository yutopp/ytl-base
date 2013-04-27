#ifndef YTL_BINARY_BUFFER_STL_HPP
#define YTL_BINARY_BUFFER_STL_HPP

#include <string>

#include "binary_buffer.hpp"

namespace ytl
{
    //
    template<template <typename> class Allocator>
    inline basic_binary_buffer<Allocator>&
        operator<<(
            basic_binary_buffer<Allocator>& lhs,
            std::string const& rhs
            )
    {
        lhs->insert( lhs->end(), rhs.begin(), rhs.end() );
        lhs->push_back( 0 );  // Null terminate

        return lhs;
    }

} // namespace ytl

#endif /*YTL_BINARY_BUFFER_STL_HPP*/
