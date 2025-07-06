/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_counter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:03 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:03 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	n_counter(int n)
{
	int	counter;

	counter = 0;
	if (n <= 0)
		counter = 1;
	while (n)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}
