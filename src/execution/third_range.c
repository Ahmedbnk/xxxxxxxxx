/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   third_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:53 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:52:53 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	third_range(int exit_status)
{
	if (exit_status == 27)
		printf("Profiling timer expired\n");
	else if (exit_status == 29)
		printf("I/O possible\n");
	else if (exit_status == 30)
		printf("Power failure\n");
	else if (exit_status == 31)
		printf("Bad system call (core dumped)\n");
	else if (exit_status == 32 || exit_status == 33)
		printf("Unknown signal %d\n", exit_status);
	else if (exit_status >= 34 && exit_status <= 64)
		printf("Real-time signal %d\n", exit_status - 34);
}
