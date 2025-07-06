/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:53:00 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:10:11 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_tokens(t_shell *sh) {
  char **ptr;

  if (!sh || !sh->splitted)
    return ;
  ptr = sh->splitted;
  while (*ptr) {
    if (is_redirection(*ptr)) {
      process_redirection_token(sh, ptr);
      ptr++;
    } else if (are_eq(*ptr, "|"))
      process_pipe_token(sh);
    ptr++;
  }
}
