#include "minishell.h"

int	check_input_error(t_shell_control_block *shell)
{
	int	single_quote;
	int	double_quote;
	int	i;

	single_quote = 0;
	double_quote = 0;
	i = 0;
	while (shell->line[i])
	{
		if (shell->line[i] == SINGLE_Q && double_quote == 0)
			single_quote = !single_quote;
		else if (shell->line[i] == DOUBLE_Q && single_quote == 0)
			double_quote = !double_quote;
		i++;
	}
	return (single_quote || double_quote);
}

int	check_error(t_shell_control_block *shell)
{
  char *str;

  str = shell->line;
  if(!str || !*str)
    return 1;
	if (check_input_error(shell))
	{
		print_error("unclosed quote\n");
    shell->exit_status = 2;
    return 1;
	}
	return (0);
}
