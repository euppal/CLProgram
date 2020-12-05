//
//  clp_parser.c
//  CLProgram
//

#include "clp_parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void _fake_error_callback(const clp_error_info_t* error_info) {}
void _fake_callback(const clp_arg_t* arg) {}

clp_parser_t* clp_parser(const clp_program_info_t* program_info) {
    clp_parser_t* parser = (clp_parser_t*)malloc(sizeof(clp_parser_t));
    parser->length = 0;
    parser->capacity = 4;
    parser->flags = (clp_recognized_flag_t*)malloc(4 * sizeof(clp_recognized_flag_t));
    parser->program_info = program_info;
    parser->error_callback = _fake_error_callback;
    parser->normal_callback = _fake_callback;
    return parser;
}
void clp_parser_destruct(clp_parser_t* parser) {
    for (size_t i = 0; i < parser->length; i++) {
        free((void*)parser->flags[i].name);
    }
    free(parser->flags);
    free((void*)parser->program_info);
    free(parser);
}
void clp_on_error(clp_parser_t* parser, CLP_ErrorCallback error_callback) {
    parser->error_callback = error_callback;
}

void fill_in_flag(clp_recognized_flag_t* next_flag, const char* info) {
    next_flag->takes_value = 0;

    size_t index = 0;
    if (info[index++] == '-') {
        if (info[index + 1] == ' ') {
            next_flag->letter = info[index];
            index++;
        } else {
            clp_library_error("Expected single-character first");
        }
    }
    if (info[index++] != ' ') {
        return;
    }
    if (info[index] == '-') {
        const size_t start = index;
        while (info[index] != 0 && info[index] != ' ') {
            index++;
        }
        const size_t length = index - start;
        next_flag->name = (char*)malloc(length + 1);
        memcpy(next_flag->name, info + start, length);
        next_flag->name[length] = 0;
    }
    if (info[index++] != ' ') {
        return;
    }
    if (strncmp(info + index, "ARG", 4) == 0) {
        next_flag->takes_value = 1;
    }
}

void clp_add_flag(clp_parser_t* parser, const char* info, CLP_ArgCallback callback) {
    const size_t new_length = parser->length + 1;
    if (new_length > parser->capacity) {
        parser->capacity *= 2;
        parser->flags = (clp_recognized_flag_t*)realloc(parser->flags, sizeof(clp_recognized_flag_t) * parser->capacity);
    }
    clp_recognized_flag_t* next_flag = parser->flags + (parser->length++);
    next_flag->letter = 0;
    next_flag->name = NULL;
    next_flag->is_required = (info[0] == '!');

    if (info[next_flag->is_required] == '-') {
        fill_in_flag(next_flag, info + next_flag->is_required);
    } else {
        next_flag->takes_value = 1;
    }
    
    next_flag->callback = callback;
}
void clp_add_normal(clp_parser_t* parser, CLP_ArgCallback callback) {
    parser->normal_callback = callback;
}

void clp_run(const clp_parser_t* parser) {
    for (int i = 0; i < parser->program_info->argc; i++) {
        const char* arg = parser->program_info->argv[i];
        if (arg[0] == '-') {
            size_t j = 0;
            for (; j < parser->length; j++) {
                clp_recognized_flag_t recognized = parser->flags[j];
                if (arg[1] == recognized.letter && arg[2] == 0) {
                    clp_arg_t clp_arg = { .flag = arg, .value = NULL };
                    if (recognized.takes_value && i + 1 < parser->program_info->argc) {
                        const char* value = parser->program_info->argv[++i];
                        clp_arg.value = value;
                    }
                    recognized.callback(&clp_arg);
                    break;
                } else if (recognized.name != NULL && (strcmp(arg, recognized.name) == 0)) {
                    clp_arg_t clp_arg = { .flag = arg, .value = NULL };
                    if (recognized.takes_value && i + 1 < parser->program_info->argc) {
                        const char* value = parser->program_info->argv[++i];
                        clp_arg.value = value;
                    }
                    recognized.callback(&clp_arg);
                    break;
                }
            }
            if (j == parser->length) {
                clp_error_info_t error_info;
                error_info.recognized = NULL;
                error_info.given = arg;
                error_info.error = CLPErrorUnrecognizedArguments;
                clp_error(parser, &error_info);
                return;
            }
        } else {
            clp_arg_t clp_arg = { .flag = NULL, .value = arg };
            parser->normal_callback(&clp_arg);
        }
    }
}
