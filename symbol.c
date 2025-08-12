#include "compiler.h"
#include "helpers/vector.h"

static void symbol_push(struct compile_process* process, struct symbol* sym)
{
    vector_push(process->symbols.table, &sym);
}

void symbol_initialize(struct compile_process* process)
{
    process->symbols.tables = vector_create(sizeof(struct vector*));
}

void symbol_new_table(struct compile_process* process)
{
    vector_push(process->symbols.tables, &process->symbols.table);

    process->symbols.table = vector_create(sizeof(struct symbol*));
}

void symbol_end_table(struct compile_process* process)
{
    struct vector* last_table = vector_back_ptr(process->symbols.tables);
    process->symbols.table = last_table;
    vector_pop(process->symbols.tables);
}

struct symbol* get_symbol(struct compile_process* process, const char* name)
{
    vector_set_peek_pointer(process->symbols.table, 0);
    struct symbol* symbol = vector_peek_ptr(process->symbols.tables);
    while(symbol)
    {
        if(S_EQ(symbol->name, name))
        {
            break;
        }
        symbol = vector_peek_ptr(process->symbols.table);
    }
    return symbol;
}

struct symbol* get_symbol_for_native_function(struct compile_process* process, const char* name)
{
    struct symbol* symbol = get_symbol(process, name);
    if(!symbol)
    {
        return NULL;
    }
    if(symbol->type != SYMBOL_TYPE_NATIVE_FUNCTION)
    {
        return NULL;
    }
    return symbol;
}

struct symbol* register_symbol(struct compile_process* process, const char* name, int type, void* data)
{
    if(get_symbol(process, name))
    {
        return NULL;
    }

    struct symbol* symbol = calloc(1,sizeof(struct symbol));
    symbol->name = name;
    symbol->type = type;
    symbol->data = data;
    symbol_push(process, symbol);
    return symbol;
}

struct node* symbol_node(struct symbol* symbol)
{
    if(symbol->type != SYMBOL_TYPE_NODE)
    {
        return NULL;
    }

    return symbol->data;
}

void symbol_build_for_variable_node(struct compile_process* process, struct node* node)
{
    compiler_error(process, "Variable not yet support\n");
}

void symbol_build_for_function_node(struct compile_process* process, struct node* node)
{
    compiler_error(process, "Functions not yet support\n");
}

void symbol_build_for_structure_node(struct compile_process* process, struct node* node)
{
    compiler_error(process, "Structures not yet support\n");
}

void symbol_build_for_union_node(struct compile_process* process, struct node* node)
{
    compiler_error(process, "Union not yet support\n");
}

void symbol_build_for_node(struct compile_process* process, struct node* node)
{
    switch(node->type)
    {
        case NODE_TYPE_VARIABLE:
            symbol_build_for_variable_node(process, node);
        break;
        case NODE_TYPE_FUNCTION:
            symbol_build_for_function_node(process, node);
        break;
        case NODE_TYPE_STRUCT:
            symbol_build_for_structure_node(process, node);
        break;
        case NODE_TYPE_UNION:
            symbol_build_for_union_node(process, node);
        break;
    }
}
