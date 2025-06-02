#include "minishell.h"

char **get_path(void)
{
	char	*path;
	char	**splited;

	path = getenv("PATH");
	splited = ft_split(path, ':');
	return splited;
}

int	how_many_strcut_in_the_array(t_data *arr_of_stracts)
{
	int number_of_structs;

	number_of_structs = 0;
	while(arr_of_stracts->word != NULL)
	{
		number_of_structs++;
		arr_of_stracts++;
	}
	return number_of_structs;
} 