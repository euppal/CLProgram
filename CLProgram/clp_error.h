//
//  clp_error.h
//  CLProgram
//

#ifndef clp_error_h
#define clp_error_h

#include <stdio.h>

#define clp_library_error(msg) printf("CLP Library Error: %s\n", msg)

typedef enum {
    CLPErrorNoError,
    CLPErrorUnrecognizedArguments
} CLPErrorType;

struct clp_recognized_flag_t;

typedef struct {
    struct clp_recognized_flag_t* recognized;
    const char* given;
    CLPErrorType error;
} clp_error_info_t;

typedef void (*CLP_ErrorCallback)(const clp_error_info_t* error_info);

struct clp_parser_t;
void clp_error(const struct clp_parser_t* parser, const clp_error_info_t* error_info);

#endif /* clp_error_h */
