//
//  main.c
//  CLProgram
//

// EXAMPLE PROGRAM

#include <stdio.h>
#include "clp.h"

void callback_help(const clp_arg_t* help_arg) {
    printf("Help requested\n");
}
void callback_file(const clp_arg_t* arg) {
    printf("File = %s\n", arg->value);
}
void callback_verbose(const clp_arg_t* arg) {
    printf("Verbose specified\n");
}
void callback_normal(const clp_arg_t* arg) {
    printf("Normal arg = %s\n", arg->value);
}
void callback_error(const clp_error_info_t* error_info) {
    switch (error_info->error) {
        case CLPErrorUnrecognizedArguments: {
            printf("Unrecognized argument '%s'\n", error_info->given);
            break;
        }
        default:
            break;
    }
}

int main(int argc, const char* argv[]) {
    clp_program_info_t* program_info = clp_program_info(argc, argv);
    clp_parser_t* parser = clp_parser(program_info);
    
    clp_on_error(parser, callback_error);
    clp_add_flag(parser, "-h --help", callback_help);
    clp_add_flag(parser, "-f --file ARG", callback_file);
    clp_add_flag(parser, "-d --verbose", callback_verbose);
    clp_add_normal(parser, callback_normal);
    clp_run(parser);
    
    clp_parser_destruct(parser);
    return 0;
}
