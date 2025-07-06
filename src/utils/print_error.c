/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:03 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:53:03 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_putchar(char c, int *counter)
// {
// 	write(2, &c, 1);
// 	(*counter)++;
// }

// void	ft_putstr(char *str, int *counter)
// {
// 	if (!str)
// 		str = "(null)";
// 	while (*str)
// 	{
// 		ft_putchar(*str, counter);
// 		str++;
// 	}
// }

// void	format_specifier(va_list arguements, char specifier, int *counter)
// {
// 	if (specifier == 's')
// 		ft_putstr((char *)va_arg(arguements, char *), counter);
// }

// int	print_error(const char *str, ...)
// {
// 	va_list	arguements;
// 	int		counter;
// 	int		i;

// 	i = 0;
// 	counter = 0;
// 	va_start(arguements, str);
// 	while (str[i])
// 	{
// 		if (str[i] == '%')
// 		{
// 			i++;
// 			format_specifier(arguements, str[i], &counter);
// 		}
// 		else
// 			ft_putchar(str[i], &counter);
// 		i++;
// 	}
// 	va_end(arguements);
// 	return (counter);
// }
