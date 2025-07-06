/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_after_geting_path.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:53 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:52:53 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_after_geting_path(char *cmd, char **av, char **path, char **env)
{
	int		i;
	char	*cmd_with_its_path;
	char	*buffer;

	i = 0;
	while (path[i])
	{
		cmd_with_its_path = buffering(path[i], "/", cmd);
		if (access(cmd_with_its_path, F_OK) == 0)
		{
			if (access(cmd_with_its_path, X_OK) == 0)
			{
				execve(cmd_with_its_path, av, env);
				buffer = buffering(buffering(cmd, ": ", 0),
						buffering(strerror(errno), "\n", 0), 0);
				exit((print(2, buffer), free_all(), errno));
			}
			else
				exit((print(2, buffering(cmd, ": ", "Permission denied\n")),
						free_all(), 126));
		}
		i++;
	}
	exit((print(2, buffering(cmd, ": ", "command not found\n")), free_all(),
			127));
}
