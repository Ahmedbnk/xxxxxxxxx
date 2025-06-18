#include "minishell.h"

static void	remove_quotes_helper(char *line, char **parsed_quote_line)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	int lock = 0;
	while (line[i])
	{
		if((line[i] == single_q || line[i] == double_q) && quote == 0 && lock ==0)
			quote = line[i];
		else if ((line[i] == single_q || line[i] == double_q)
			&& quote == line[i])
			quote = 0;
		else 
			(*parsed_quote_line)[j++] = line[i];
		if(line[i] == PROTECT &&  lock == 0)
			lock = 1;
		else if(line[i] == PROTECT && lock == 1)
			lock = 0;
		i++;
	}
	(*parsed_quote_line)[j] = '\0';
}

void	remove_quotes(char **line)
{
	char	*line_without_quotes;

	line_without_quotes = ft_malloc(ft_strlen(*line) + 1, 1);
	remove_quotes_helper(*line, &line_without_quotes);
	*line = line_without_quotes;
}

void remove_quotes_from_args(char **splitted)
{
  int i;

  i = 0;
  while(splitted[i])
  {
    remove_quotes(&splitted[i]);
    i++;
  }
}
