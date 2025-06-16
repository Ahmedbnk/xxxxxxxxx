#include "minishell.h"

int	how_many_dallar_to_expand(char *str, int heredoc_flag)
{
	int	i;
	int	counter;

	// Safety check
	if (!str)
		return 0;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (heredoc_flag || should_i_expand(str, i)) && ft_isalnum(str[i + 1]))
			counter++;
		i++;
	}
	return (counter);
}
