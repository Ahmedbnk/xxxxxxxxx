#include "minishell.h"

int is_quote(char c)
{
    return (c == SINGLE_Q || c == DOUBLE_Q);
}