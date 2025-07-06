/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_red_symbole.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:00 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:10:11 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_red_symbole(char *str)
{
	if (!str)
		return (0);
	if (are_eq(str, "<") || are_eq(str, ">"))
		return (1);
	if (are_eq(str, ">>") || are_eq(str, "<<"))
		return (1);
	return (0);
}
