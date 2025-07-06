/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 18:55:02 by nkasimi           #+#    #+#             */
/*   Updated: 2024/11/07 17:02:34 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_itoa(int n)
{
	int		len;
	char	*a;

	if (n == -2147483648)
		return (ft_strdup("-2147483648", 1));
	len = n_counter(n);
	a = ft_malloc((len + 1) * sizeof(char), 1);
	if (n == 0)
		a[0] = '0';
	if (n > 0)
		fill_n_str(a, n);
	else if (n < 0)
	{
		a[0] = '-';
		fill_n_str(a + 1, -n);
	}
	a[len] = '\0';
	return (a);
}
