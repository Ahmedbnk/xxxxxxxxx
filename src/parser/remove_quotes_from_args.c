#include "minishell.h"

static void	rm_quotes_from_one_str_helper(t_shell_control_block *sh, char *line, char **parsed_quote_line)
{
	(void)sh;
	int i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (line[i])
	{
		if (is_quote(line[i]) && quote == 0 && !is_protected(sh, line, i))
			quote = line[i];
		else if (is_quote(line[i]) && quote == line[i])
			quote = 0;
		else
			(*parsed_quote_line)[j++] = line[i];
		if(is_quote(line[i]) && is_protected(sh, line, i))
			i = (i +ft_strlen(sh->porotect_var));
		i++;
	}
	(*parsed_quote_line)[j] = '\0';
}

void	rm_quotes_from_one_str(t_shell_control_block *sh, char **line)
{
	char	*line_without_quotes;

	line_without_quotes = ft_malloc(ft_strlen(*line) + 1, 1);
	rm_quotes_from_one_str_helper(sh, *line, &line_without_quotes);
	*line = line_without_quotes;
}
