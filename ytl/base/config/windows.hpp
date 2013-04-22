#ifndef YTL_BASE_CONFIG_WINDOWS_HPP
#define YTL_BASE_CONFIG_WINDOWS_HPP

// ????
/*namespace ytl
{
	namespace windows
	{*/

#ifndef NOMINMAX
# define NOMINMAX
#endif

#include <Windows.h>

#ifdef NOMINMAX
# undef NOMINMAX
#endif

/*	}
} // namespace ytl*/

#endif /*YTL_BASE_CONFIG_WINDOWS_HPP*/