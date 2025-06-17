#include "minishell.h"

int find_char_in_str(char *str, char c)
{
  while(*str)
  {
    if(*str == c)
      return 1;
    str++;
  }
  return 0;
}
char *ft_charremove(const char *s1, char c)
{
	int		i;
	int		j;
	int		len;
	char	*result;
	
	if (!s1)
		return (NULL);
	
	len = ft_strlen(s1);
	result = (char *)ft_malloc(sizeof(char) * (len + 1), 1);
	if (!result)
		return (NULL);
	
	i = 0;
	j = 0;
	// Copy all characters except the specified character 'c'
	while (s1[i])
	{
		if (s1[i] != c)
		{
			result[j] = s1[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	
	return (result);
}

char **creat_new_splitted(t_list *list)
{
  char **new_splitted;
  char *array;
  int flag;
  flag = 0;
  int j;
  j = 0;
  new_splitted = ft_malloc((ft_lstsize(list)+1) * sizeof(char *), 1);
  while(list)
  {
    array = (char *)list->content;
    if (flag != 2)
      if (find_char_in_str(array, 14))
        flag++;
    if (flag == 2 && *array != 14)
      new_splitted[j] = ft_charremove(ft_strjoin(new_splitted[j], array), 14);
    else
      new_splitted[j] = ft_charremove(array, 14);
    j++;
    list = list->next;
  }
  new_splitted[j] = NULL;

  return new_splitted;
}


char **split_after_expantion(char **str)
{
  int i;
  char **ptr;
  t_list *node;
  t_list *list;
  list =NULL;
  i = 0;
  
  printf("DEBUG: split_after_expantion called\n");
  while(str[i])
  {
    printf("DEBUG: Processing string[%d]: '%s'\n", i, str[i]);
    ptr = test_split(str[i]);
    printf("DEBUG: After test_split, got:\n");
    int j = 0;
    while(ptr[j])
    {
      printf("DEBUG:   ptr[%d]: '%s'\n", j, ptr[j]);
      j++;
    }
    while(*ptr)
    {
      node = ft_lstnew(*ptr);
      ft_lstadd_back(&list, node);
      ptr++;
    }
    i++;
  }
  char **result = creat_new_splitted(list);
  printf("DEBUG: Final result:\n");
  i = 0;
  while(result[i])
  {
    printf("DEBUG:   result[%d]: '%s'\n", i, result[i]);
    i++;
  }
  return (result);
}
