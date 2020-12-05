//
//  clp_program.c
//  CLProgram
//

#include "clp_proginfo.h"
#include <stdlib.h>

clp_program_info_t* clp_program_info(const int argc, const char* argv[]) {
    clp_program_info_t* program_info = (clp_program_info_t*)malloc(sizeof(clp_program_info_t));
    program_info->name = argv[0];
    program_info->argc = argc - 1;
    program_info->argv = argv + 1;
    return program_info;
}
