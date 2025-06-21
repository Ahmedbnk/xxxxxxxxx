#include "minishell.h"

int is_quote(char c)
{
    return (c == single_q || c == double_q);
}