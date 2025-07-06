/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_splitted.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:03 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:03 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_splitted(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
	{
		printf("%s\n", splitted[i]);
		i++;
	}
}
