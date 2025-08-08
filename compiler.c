#include "compiler.h"
#include <stdarg.h>
#include <stdlib.h>

struct lex_process_functions compiler_lex_functions = {
     .next_char=compile_process_next_char,
     .peek_char=compile_process_peek_char,
     .push_char=compile_process_push_char
};

void compiler_error(struct compile_process *compiler, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "on line %i, col %i in file %s\n", compiler->pos.line, compiler->pos.col, compiler->pos.filename);
    exit(-1);
}

void compiler_warning(struct compile_process *compiler, const char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    va_end(args);
    fprintf(stderr, "on line %i, col %i in file %s\n", compiler->pos.line, compiler->pos.col, compiler->pos.filename);
}


int compile_file(const char *file_name, const char *out_file, int flags)
{
    struct compile_process *process = compile_process_create(file_name, out_file, flags);
    if(process == NULL)
    {
        return COMPILER_FAILED_WITH_EORRORS;
    }

    //Preform lexical analysis
    struct lex_process *lex_process = lex_process_create(process, &compiler_lex_functions, NULL);
    if (lex_process == NULL)
    {
        return COMPILER_FAILED_WITH_EORRORS;
    }
    if (lex(lex_process) != LEXIT_ANALYSIS_SUCESS)
    {
        return COMPILER_FAILED_WITH_EORRORS;
    }
    process->token_vec = lex_process->token_vec;
    //Preform parsing

    //Preform code generation

    return COMPILER_SUCCESS;
}