/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:53 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:52:53 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_range(int exit_status)
{
	if (exit_status == 1)
		printf("Hangup\n");
	else if (exit_status == 2)
		printf("\n");
	else if (exit_status == 3)
		printf("Quit (core dumped)\n");
	else if (exit_status == 4)
		printf("Illegal instruction (core dumped)\n");
	else if (exit_status == 5)
		printf("Trace/breakpoint trap (core dumped)\n");
	else if (exit_status == 6)
		printf("Aborted (core dumped)\n");
	else if (exit_status == 7)
		printf("Bus error (core dumped)\n");
	else if (exit_status == 8)
		printf("Floating point exception (core dumped)\n");
	else if (exit_status == 9)
		printf("Killed\n");
	else if (exit_status == 10)
		printf("User defined signal 1\n");
	else if (exit_status == 11)
		printf("Segmentation fault (core dumped)\n");
	else if (exit_status == 12)
		printf("User defined signal 2\n");
}
