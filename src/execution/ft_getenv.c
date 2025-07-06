/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:53 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 18:56:08 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(void)
{
	char	**ptr;
	int		start;
	int		end;
	int		i;
	t_shell	*shell_ptr;

	shell_ptr = get_shell_pointer(NULL);
	ptr = shell_ptr->env_cpy;
	i = 0;
	while (ptr[i])
	{
		if (compare_env_var(ptr[i], "PATH"))
		{
			get_start_and_end(ptr[i], &start, &end);
			return (ft_substr(ptr[i], start, (end - start)));
		}
		i++;
	}
	return (NULL);
}
