#include "minishell.h"

int	is_redirection(char *str)
{
	if (!str)
		return (0);
	return (are_they_equal(str, ">") || are_they_equal(str, "<") || 
		are_they_equal(str, ">>"));
}
