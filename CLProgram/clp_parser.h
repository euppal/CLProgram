//
//  clp_parser.h
//  CLProgram
//

#ifndef clp_parser_h
#define clp_parser_h

#include "clp_args.h"
#include "clp_proginfo.h"
#include "clp_error.h"
#include <stddef.h>

typedef void (*CLP_ArgCallback)(const clp_arg_t* arg);

typedef struct clp_recognized_flag_t {
    char letter;
    char* name;
    int takes_value;
    int is_required;
    CLP_ArgCallback callback;
} clp_recognized_flag_t;

typedef struct clp_parser_t {
    size_t length;
    size_t capacity;
    clp_recognized_flag_t* flags;
    const clp_program_info_t* program_info;
    CLP_ArgCallback normal_callback;
    CLP_ErrorCallback error_callback;
} clp_parser_t;


clp_parser_t* clp_parser(const clp_program_info_t* program_info);
void clp_parser_destruct(clp_parser_t* parser);
void clp_on_error(clp_parser_t* parser, CLP_ErrorCallback error_callback);

void clp_add_flag(clp_parser_t* parser, const char* info, CLP_ArgCallback callback);
void clp_add_normal(clp_parser_t* parser, CLP_ArgCallback callback);

void clp_run(const clp_parser_t* parser);

#endif /* clp_parser_h */
