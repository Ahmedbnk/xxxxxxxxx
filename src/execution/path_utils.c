#include "minishell.h"

char **get_path(void)
{
	char	*path;
	char	**splited;

	path = getenv("PATH");
	if (!path)
		return (NULL);
	splited = ft_split(path, ':');
	return (splited);
}

static char *build_cmd_path(char *path, char *cmd)
{
	char *cmd_with_slash;
	char *full_path;

	cmd_with_slash = ft_strjoin("/", cmd);
	if (!cmd_with_slash)
		return (NULL);
	full_path = ft_strjoin(path, cmd_with_slash);
	free(cmd_with_slash);
	return (full_path);
}

int find_cmd_in_path(char *cmd, char **path)
{
	int i;
	char *full_path;

	i = 0;
	while (path[i])
	{
		full_path = build_cmd_path(path[i], cmd);
		if (!full_path)
			return (-1);
		if (access(full_path, F_OK) == 0)
		{
			free(full_path);
			return (i);
		}
		free(full_path);
		i++;
	}
	return (-1);
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