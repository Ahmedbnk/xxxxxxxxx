#include "minishell.h"



static int find_and_update_var(char **env, char *var)
{
    int i;

    i = 0;

    while (env[i])
    {
        if (compare_env_var(env[i], var))
        {
            env[i] = ft_strdup(var, 0);
            return 1;
        }
        i++;
    }
    return 0;
}

static char **add_var_to_env(char **env , char *var)
{
    char **new_env;
    new_env = ft_malloc((len_of_two_d_array(env)+ 2) * sizeof(char *), 0);
    int i;
    i = 0;
    while(*env)
    {
        new_env[i] = ft_strdup(*env, 0);
        i++;
        env++;
    }
    new_env[i++] = ft_strdup(var, 0);
    new_env[i] = NULL;
    return new_env;
}



 static void sort_env(char **env)
{
	int i;
	int j;
	i = 0;
	char *tmp;
		while(env[i])
		{
            j = i+1;
            while(env[j])
            {
                if(ft_strcmp(env[i], env[j]) > 0)
                {
                    tmp = env[i];
                    env[i] = env[j];
                    env[j] = tmp;
                }
                j++;
            }
			i++;
		}
    remove_var_from_env(&env, "_");
        print_env(env);
}

void export(t_shell_control_block *s, char **to_export)
{
    if(!to_export || !*to_export)
    {
        sort_env(s->env_of_export);
        return ;
    }
    while(*to_export)
    {
        if(!is_valid_var(*to_export));
        else
        {
        if (find_and_update_var(s->env_of_export, *to_export));
        else
            s->env_of_export = add_var_to_env(s->env_of_export , *to_export);
        if(!is_it_key_value(*to_export))
            ;
        else if (find_and_update_var(s->env_cpy, *to_export));
        else
            s->env_cpy = add_var_to_env(s->env_cpy , *to_export);
        }
        to_export++;
    }
}
