/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocate_and_init_expand_list.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenkrar <abenkrar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/04 17:52:52 by abenkrar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	allocat_and_init(t_expand **expand_list, int how_much_to_expand,
		int heredoc_flag)
{
	allocat_arr_of_structs_list(expand_list, how_much_to_expand);
	init_arr_of_structs_list(*expand_list, how_much_to_expand, heredoc_flag);
}
