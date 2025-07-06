/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:59 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:10:11 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_type	get_token_type(const char *str)
{
	if (are_eq(str, "|"))
		return (PIPE);
	else if (are_eq(str, "<"))
		return (REDIR_IN);
	else if (are_eq(str, ">"))
		return (REDIR_OUT);
	else if (are_eq(str, ">>"))
		return (REDIR_APPEND);
	else if (are_eq(str, "<<"))
		return (HEREDOC);
	else
		return (WORD);
}
