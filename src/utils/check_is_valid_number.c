/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_valid_number.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:01 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:01 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static const char	*skip_whitespace_and_sign(const char *str, int *sign)
{
	*sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

static int	parse_digits(const char *str, int sign, long long max)
{
	long long	result;

	result = 0;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		if (result > max / 10)
			return (0);
		if (result == max / 10)
		{
			if (sign == 1 && (*str - '0') > max % 10)
				return (0);
			if (sign == -1 && (*str - '0') > (max % 10) + 1)
				return (0);
		}
		result = result * 10 + (*str - '0');
		str++;
	}
	return (1);
}

int	check_is_valid_number(const char *str)
{
	long long	max;
	int			sign;

	max = 9223372036854775807;
	if (!str || !*str)
		return (0);
	str = skip_whitespace_and_sign(str, &sign);
	if (!*str)
		return (0);
	return (parse_digits(str, sign, max));
}
