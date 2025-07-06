/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkasimi <nkasimi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:52:52 by abenkrar          #+#    #+#             */
/*   Updated: 2025/07/05 14:11:43 by nkasimi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset(char ***env, char **vars)
{
	while (*vars)
	{
		if (is_the_var_in_env(*env, *vars))
			remove_var_from_env(env, *vars);
		vars++;
	}
	return (0);
}

// int main(int argc, char *argv[], char *env[])
// {
//   (void ) argv;
//   (void ) argc;
//
//   char **env_cpy = copy_2d(env);
//   char *av[] = {"b=1337", "jlj", "z=1337!","13=","a=45", NULL};
//   char *av1[] = {"b=1337", "a", "z=1337!","13=", NULL};
//   printf("%d\n", len_of_two_d_array(env_cpy));
//   export(&env_cpy, av);
//   printf("%d\n", len_of_two_d_array(env_cpy));
//   unset(&env_cpy,  av1);
//   print_env(env_cpy);
//      free_memory(*get_garbage_pointer());
//   return (0);
// }
//
