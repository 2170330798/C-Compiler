#include "compiler.h"

#define PRIMTIVIE_TYPE_TOTAL 7
const char* primitive_types[PRIMTIVIE_TYPE_TOTAL] = {
    "void", "char", "short", "int", "long", "float", "double"
};

bool token_is_keywords(struct token* token, const char* value)
{
    printf("is_keywords?\n");
    return token->type == TOKEN_TYPE_KEYWORD && S_EQ(token->sval, value);
}

bool token_is_symbol(struct token* token, char c)
{
    printf("is_keywords?\n");
    return token->type == TOKEN_TYPE_SYMBOL && token->cval == c;
}

bool token_is_operator(struct token* token, const char* val)
{
    return token->type == TOKEN_TYPE_OPERATOR && S_EQ(token->sval, val);
}

bool token_is_nl_or_comment_or_newline_seperator(struct token* token)
{
    printf("is_nl_or_comment_or_newline_seperator?\n");
    return token->type == TOKEN_TYPE_NEWLINE || token->type == TOKEN_TYPE_COMMENT || token_is_symbol(token, '\\');
}

bool token_is_primitive_keyword(struct token* token)
{
    if(token->type != TOKEN_TYPE_KEYWORD)
        return false;
    
    for (int i = 0; i < PRIMTIVIE_TYPE_TOTAL ; i++)
    {
        if(S_EQ(primitive_types[i], token->sval))
            return true;
    }
    return false;
}