#include "minishell.h"

void get_start_and_end(char *str, int *start, int *end)
{
  int i;
  i = 0;
  while(str[i])
  {
    if(str[i] == '=')
      *start = i+1;
    i++;
  }
  *end = i;
}

int count_number_of_qute(char *str)
{
  int number_of_qute;
  number_of_qute = 0;

  while(*str)
  {
    if(is_quote(*str))
      number_of_qute++;
    str++;
  }
  return number_of_qute;
}

char *protect_str(t_shell_control_block *sh ,char *str)
{
  char *new_str;
  int i;
  int j;
  int size;
  size = ft_strlen(str) + (ft_strlen(sh->porotect_var) * count_number_of_qute(str)) + 1;
  new_str = ft_malloc(size, 1);
  i = 0;
  while (*str)
  {
    j = 0;
    if(is_quote(*str))
    {
      new_str[i++] = *str;
      while(sh->porotect_var[j])
        new_str[i++] = sh->porotect_var[j++];
    }
    else
      new_str[i++] = *str;
    str++;
  }
  new_str[i] = '\0';
  return new_str;
}

char *get_env_var(t_shell_control_block *shell , t_expand data)
{
  char **ptr = shell->env_cpy;
  char *value;
  int start;
  int end;

  int i ;
  i = 0;
  while(ptr[i])
  {
    if(compare_env_var(ptr[i], (data.to_expand)+1))
    {
      get_start_and_end(ptr[i], &start, &end);
      value = ft_substr(ptr[i], start, (end-start));
      value = protect_str(shell, value);
      return value;
    }
    i++;
  }
  return NULL;
}

char	*ft_get_env_var(t_shell_control_block *shell, char *var_name)
{
	int		i;
	char	*env_var;

	if (!shell->env_cpy || !var_name)
		return (NULL);
	
	i = 0;
	while (shell->env_cpy[i])
	{
		if (ft_strncmp(shell->env_cpy[i], var_name, ft_strlen(var_name)) == 0 &&
			shell->env_cpy[i][ft_strlen(var_name)] == '=')
		{
			env_var = ft_strdup(shell->env_cpy[i] + ft_strlen(var_name) + 1, 1);
			return (env_var);
		}
		i++;
	}
	return (NULL);
}
