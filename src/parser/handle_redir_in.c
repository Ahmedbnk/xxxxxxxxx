/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redir_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:59 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 16:50:52 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_redir_in(char *str, char **in_file_name, t_shell *shell)
{
	char	*buffer;
	int		fd;

	shell = get_shell_pointer(NULL);
	buffer = NULL;
	*in_file_name = str;
	fd = ft_open(*in_file_name, O_RDWR | O_TRUNC, 0766);
	if (fd < 0)
	{
		shell->exit_status = 1;
		return ;
	}
	buffer = read_file(str);
	if (!buffer)
		return ;
	write(fd, buffer, ft_strlen(buffer));
	ft_close(fd);
}
