//
//  clp_proginfo.h
//  CLProgram
//

#ifndef clp_proginfo_h
#define clp_proginfo_h

typedef struct {
    const char* name;
    int argc;
    const char** argv;
} clp_program_info_t;

clp_program_info_t* clp_program_info(const int argc, const char* argv[]);

#endif /* clp_proginfo_h */
