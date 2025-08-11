#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "helpers/vector.h"

struct compile_process * compile_process_create(const char *file_name, const char *filename_out, int flag)
{
    FILE *in_file = fopen(file_name, "r");
    if (in_file == NULL)
    { 
        return NULL;
    }
    FILE *out_file = fopen(filename_out, "w");
    if (out_file == NULL)
    {
        return NULL;
    }
    
    struct compile_process *process = calloc(1, sizeof(struct compile_process));
    process->node_vec = vector_create(sizeof(struct node*));
    process->node_tree_vec = vector_create(sizeof(struct node*));
    process->flags = flag;
    process->c_file.fp = in_file;
    process->out_file = out_file;
    return process;
}

char compile_process_next_char(struct lex_process *lex_process)
{
    struct compile_process *compiler = lex_process->compiler;
    compiler->pos.col += 1;
    char c = getc(compiler->c_file.fp);
    if (c == '\n')
    {
        compiler->pos.line += 1;
        compiler->pos.col = 0;
    }
    return c;
}

char compile_process_peek_char(struct lex_process *lex_process)
{
    struct compile_process *compiler = lex_process->compiler;
    char c = getc(compiler->c_file.fp);
    ungetc(c, compiler->c_file.fp);
    return c;
}

void compile_process_push_char(struct lex_process *lex_process, char c)
{
    struct compile_process *compiler = lex_process->compiler;
    ungetc(c, compiler->c_file.fp);
}