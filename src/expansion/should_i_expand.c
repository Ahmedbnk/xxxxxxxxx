#include "minishell.h"

int	should_i_expand(char *str, int index)
{
	char	quote;

	// Safety checks
	if (!str || index < 0)
		return 0;

	quote = 0;
	quote = is_between_quotes(str, index);
	if (quote == single_q || str[index + 1] == '\0' || str[index
		+ 1] == single_q || str[index + 1] == double_q)
		return (0);
	else
		return (1);
}
