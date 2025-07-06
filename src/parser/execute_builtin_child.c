/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:59 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:10:11 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin_child(t_shell *shell)
{
	int	status;

	if (are_eq(*shell->cmd_and_args, "pwd"))
		exit((printf("%s\n", pwd(&status)), free_all(), status));
	else if (are_eq(*shell->cmd_and_args, "env"))
		exit((status = print_env(shell->env_cpy), free_all(), status));
	else if (are_eq(*shell->cmd_and_args, "echo"))
		exit((status = echo(shell->cmd_and_args), free_all(), status));
	else if (are_eq(*shell->cmd_and_args, "cd"))
		exit((status = cd(shell->env_cpy, shell->cmd_and_args), free_all(),
				status));
	else if (are_eq(*shell->cmd_and_args, "export"))
		exit((status = export(shell, shell->cmd_and_args + 1), free_all(),
				status));
	else if (are_eq(*shell->cmd_and_args, "unset"))
		exit((status = unset(&shell->env_cpy, shell->cmd_and_args + 1),
				free_all(), status));
	else if (are_eq(*shell->cmd_and_args, "exit"))
	{
		shell->exit_status = my_exit(shell->cmd_and_args + 1);
		if (shell->exit_status != 1)
			exit((status = shell->exit_status, free_all(), status));
	}
}
