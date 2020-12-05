# The CLP Library

> This is a simple library for command line programs. As it is not finished, please let me know (and optionally fix) any bugs you find!  

CLP operates with simply what is provided in a standard main function. You simply register flags and whether or not they have arguments, and then supply a callback. It is that simple.

```c
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
```
