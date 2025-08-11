#include "compiler.h"

struct expressionable_op_precedence_group op_precedence[TOTAL_OPERATOR_GROUPS] = {
    {.operators={"++", "--", "()", "[]", "(", "[", "->", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT},
    {.operators={"*", "/", "%", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT},
    {.operators={"<<", ">>", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT},
    {.operators={"<", "<=", ">", ">=", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT},
    {.operators={"==", "!=", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT},
    {.operators={"&", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT},
    {.operators={"^", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT},
    {.operators={"|", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT},
    {.operators={"&&", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT},
    {.operators={"||", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT},
    {.operators={"?", NULL}, .associtivity=ASSOCIATIVITY_RIGHT_TO_LEFT},
    {.operators={"=","+=", "-=", "*=", "/=", "%=", "<<=", ">>=", "^=", "|=", "&=", NULL}, .associtivity=ASSOCIATIVITY_RIGHT_TO_LEFT},
    {.operators={",", NULL}, .associtivity=ASSOCIATIVITY_LEFT_TO_RIGHT}
};