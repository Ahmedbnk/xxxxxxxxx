/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:02 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:25:01 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	**get_fd_pointer(void)
{
	static int	*ptr;

	return (&ptr);
}

void	init_fd_lst(int *ptr)
{
	int	i;

	i = 0;
	while (i < 1025)
		ptr[i++] = -1;
}

void	make_fd_lst(void)
{
	int	**ptr;

	ptr = get_fd_pointer();
	*ptr = ft_malloc(1025 * sizeof(int), 1);
	init_fd_lst(*ptr);
}
