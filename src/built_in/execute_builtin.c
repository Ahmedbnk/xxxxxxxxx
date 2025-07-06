/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:51 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:10:11 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_shell *shell)
{
	int	status;

	if (are_eq(*shell->cmd_and_args, "pwd"))
	{
		printf("%s\n", pwd(&status));
		shell->exit_status = status;
	}
	else if (are_eq(*shell->cmd_and_args, "env"))
		shell->exit_status = print_env(shell->env_cpy);
	else if (are_eq(*shell->cmd_and_args, "echo"))
		shell->exit_status = echo(shell->cmd_and_args);
	else if (are_eq(*shell->cmd_and_args, "cd"))
		shell->exit_status = cd(shell->env_cpy, shell->cmd_and_args);
	else if (are_eq(*shell->cmd_and_args, "export"))
		shell->exit_status = export(shell, shell->cmd_and_args + 1);
	else if (are_eq(*shell->cmd_and_args, "unset"))
		shell->exit_status = unset(&shell->env_cpy, shell->cmd_and_args + 1);
	else if (are_eq(*shell->cmd_and_args, "exit"))
	{
		shell->exit_status = my_exit(shell->cmd_and_args + 1);
		if (shell->exit_status != 1)
			exit((status = shell->exit_status, free_all(), status));
	}
}
