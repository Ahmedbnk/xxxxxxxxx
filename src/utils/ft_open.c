/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:01 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:01 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_fd_to_lst(int fd)
{
	int	*ptr;

	if (fd < 0)
		return ;
	ptr = *(get_fd_pointer());
	if (ptr[fd] == -1)
		ptr[fd] = 1;
}

int	ft_open(const char *pathname, int flags, mode_t mode)
{
	int	fd;

	if (!pathname)
		return ((errno = EFAULT, -1));
	fd = open(pathname, flags, mode);
	if (fd < 0)
		perror(pathname);
	add_fd_to_lst(fd);
	return (fd);
}
