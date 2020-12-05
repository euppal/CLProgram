//
//  clp_util.h
//  CLProgram
//

#ifndef clp_util_h
#define clp_util_h

#include <unistd.h>

typedef enum {
    Linux,
    Mac,
    Windows
} clp_platform_t;

extern const clp_platform_t CLP_PLATFORM;

#ifdef _POSIX_VERSION
#define CLP_SUPPORTS_COLORS isatty(STDOUT_FILENO)
#else
#define CLP_SUPPORTS_COLORS 0
#endif


#endif /* clp_util_h */
