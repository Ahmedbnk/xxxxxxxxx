#include "minishell.h"

void get_start_and_end(char *str, int *start, int *end)
{
  int i;
  i = 0;
  
  // Safety checks
  if (!str || !start || !end)
    return;
    
  *start = 0;
  *end = 0;
  
  while(str[i])
  {
    if(str[i] == '=')
      *start = i+1;
    i++;
  }
  *end = i;
}

int	is_between_lock(char *line, int index)
{
	int	i;
	int	lock;

	i = 0;
	lock = 0;
	while (line[i])
	{
		if ((line[i] ==14) && lock == 0)
			lock = 1;
		else if (line[i] ==14 && lock == 1)
			lock = 0;
		if (i == index)
			return (lock);
		i++;
	}
	return (0);
}

char *protect_str(char *str)
{
  char *new_str;
  
  // Safety check
  if (!str)
    return NULL;
    
  new_str = ft_malloc(ft_strlen(str) +3, 1);
  if (!new_str)
    return NULL;
    
  *new_str =14;
  int i;
  i = 1;
  while (*str)
  {
    new_str[i++] = *str;
    str++;
  }
  new_str[i] =14;
  new_str[i+1] = '\0';
  return new_str;
}

int is_var_exist(char *var1, char *var2)
{
    int i ;
    i = 0;
    
    // Safety checks
    if (!var1 || !var2)
        return 0;
    
    while(var2[i] || var1[i] != '=')
    {
        if(var1[i] != var2[i])
            return 0;
        i++;
    }
    return 1;
}

char *get_env_var(t_shell_control_block *shell , t_expand data)
{
  char **ptr = shell->env_cpy;
  char *value;
  int start;
  int end;

  int i ;
  i = 0;
  
  // Safety checks
  if (!shell || !ptr || !data.to_expand)
    return NULL;
  
  while(ptr[i])
  {
    if(ptr[i] && is_var_exist(ptr[i], (data.to_expand)+1))
    {
      get_start_and_end(ptr[i], &start, &end);
      value = ft_substr(ptr[i], start, (end-start));
      value = protect_str(value);
      return value;
    }
    i++;
  }
  return NULL;
}


static void	split_helper(char **splitted, char *s, int i, int k)
{
	int	start;

	start = 0;
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		start = i;
		while (s[i] && (!is_space(s[i]) || (is_space(s[i])
					&& !is_between_lock(s, i))))
			i++;
		if (i > start)
			splitted[k++] = ft_substr(s, start, i - start);
	}
	// Handle empty string case
	if (ft_strlen(s) == 0)
		splitted[k++] = ft_strdup("", 1);
	splitted[k] = NULL;
}
char	**test_split(char const *s)
{
	char	**splitted;
	int		i;
	int		k;

	if (!s)
		return (NULL);
	splitted = ft_malloc((ft_w_counter(s) + 1) * sizeof(char *), 1);
	i = 0;
	k = 0;
	split_helper(splitted, (char *)s, i, k);
	return (splitted);
}
