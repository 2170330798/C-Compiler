#include "compiler.h"

bool token_is_keywords(struct token* token, const char* value)
{
    return token->type == TOKEN_TYPE_KEYWORD && S_EQ(token->sval, value);
}