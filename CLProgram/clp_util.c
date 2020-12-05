//
//  clp_util.c
//  CLProgram
//

#include "clp_util.h"

#ifdef __linux__
const clp_platform_t CLP_PLATFORM = Linux;
#elif __APPLE__
const clp_platform_t CLP_PLATFORM = Mac;
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
const clp_platform_t CLP_PLATFORM = Windows;
#endif
