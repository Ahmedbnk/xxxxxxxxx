#include "minishell.h"

t_type	get_type_type(const char *str)
{
	if (are_they_equal(str, "|"))
		return (PIPE);
	else if (are_they_equal(str, "<"))
		return (REDIR_IN);
	else if (are_they_equal(str, ">"))
		return (REDIR_OUT);
	else if (are_they_equal(str, ">>"))
		return (REDIR_APPEND);
	else if (are_they_equal(str, "<<"))
		return (HEREDOC);
	else
		return (WORD);
}

void fill_the_list(t_token * list, char **arr)
{
  int i;
  i = 0;
  while(arr[i])
  {
    list[i].type = get_type_type(arr[i]);
    list[i].word = ft_strdup(arr[i], 1);
    i++;
  }
    list[i].word = 0;
    list[i].type = -1;
}


int check_syntax_error(t_token *data, int len)
{
  int i; i = 0;
  while(i < len)
  { 
    if(data[i].type == PIPE && (i == 0 || len - 1 == i))
      return((print_error("error near | \n"), 1));
    else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type == PIPE)
      return((print_error("error near | \n"), 1));
    // else if (data[i].type != PIPE && data[i].type != WORD && data[i + 1].type != WORD)
    //   return((print_error("error near new line \n"), 1));
    // else if (data[i].type != PIPE && data[i].type != WORD && len -1 == i)
    //   return((print_error("error near new line \n"), 1));
    i++;
  }
  return 0;
}

t_token *make_token(t_shell_control_block *shell)
{
	int		i;
	int		token_count;
	t_token	*tokenized;

	i = 0;
	token_count = 0;
	while (shell->splitted[i])
	{
		if (are_they_equal(shell->splitted[i], "|"))
			token_count++;
		else if (are_they_equal(shell->splitted[i], "<"))
			token_count++;
		else if (are_they_equal(shell->splitted[i], ">"))
			token_count++;
		else if (are_they_equal(shell->splitted[i], ">>"))
			token_count++;
		else if (are_they_equal(shell->splitted[i], "<<"))
			token_count++;
		i++;
	}

	tokenized = ft_malloc((token_count + 1) * sizeof(t_token), 1);
	i = 0;
	token_count = 0;
	while (shell->splitted[i])
	{
		if (are_they_equal(shell->splitted[i], "|"))
		{
			tokenized[token_count].type = PIPE;
			tokenized[token_count].word = shell->splitted[i];
			token_count++;
		}
		else if (are_they_equal(shell->splitted[i], "<"))
		{
			tokenized[token_count].type = REDIR_IN;
			tokenized[token_count].word = shell->splitted[i];
			token_count++;
		}
		else if (are_they_equal(shell->splitted[i], ">"))
		{
			tokenized[token_count].type = REDIR_OUT;
			tokenized[token_count].word = shell->splitted[i];
			token_count++;
		}
		else if (are_they_equal(shell->splitted[i], ">>"))
		{
			tokenized[token_count].type = REDIR_APPEND;
			tokenized[token_count].word = shell->splitted[i];
			token_count++;
		}
		else if (are_they_equal(shell->splitted[i], "<<"))
		{
			tokenized[token_count].type = HEREDOC;
			tokenized[token_count].word = shell->splitted[i];
			token_count++;
		}
		i++;
	}
	tokenized[token_count].type = -1;
	tokenized[token_count].word = NULL;
	return (tokenized);
}
