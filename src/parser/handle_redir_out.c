/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_out.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:59 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:23:28 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_out(char *str, char **file_name, t_shell *shell)
{
	int	fd;

	*file_name = str;
	fd = ft_open(str, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
	{
		shell->exit_status = 1;
		return ;
	}
	ft_close(fd);
}
