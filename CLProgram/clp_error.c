//
//  clp_error.c
//  CLProgram
//

#include "clp_error.h"
#include "clp_parser.h"

void clp_error(const struct clp_parser_t* parser, const clp_error_info_t* error_info) {
    parser->error_callback(error_info);
}
