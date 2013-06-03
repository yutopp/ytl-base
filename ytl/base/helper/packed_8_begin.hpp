#include "../config/compiler.hpp"

#if defined( YTL_C_MSVC )

# pragma pack( push, 8 )

#elif defined( YTL_C_GCC )

# pragma pack( 8 )

#else

# error Not supported...

#endif