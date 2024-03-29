#ifndef YTL_BUFFER_RUNNABLE_BUFFER_ALLOCATOR_HPP
#define YTL_BUFFER_RUNNABLE_BUFFER_ALLOCATOR_HPP

#include "../config/platform.hpp"

#ifdef YTL_WINDOWS
# include "detail/windows_runnable_buffer_allocator.hpp"
#else
# error Not supported...
#endif

namespace ytl
{
    template<typename T>
    class runnable_buffer_allocator 
#ifdef YTL_WINDOWS
        : public detail::windows::runnable_buffer_allocator<T>
#else
# error "Except Windows, runnable_buffer_allocator not supported..."
#endif
    {};

} // namespace ytl

#endif /*YTL_BUFFER_RUNNABLE_BUFFER_ALLOCATOR_HPP*/
