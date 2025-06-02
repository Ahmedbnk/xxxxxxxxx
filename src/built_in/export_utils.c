#include "minishell.h"

int find_and_update_var(char **env, char *var)
{
    int i;

    i = 0;
    while (env[i])
    {
        if (compare_env_var(env[i], var))
        {
            env[i] = ft_strdup(var);
            return 1;
        }
        i++;
    }
    return 0;
}

char **add_var_to_env(char **env, char *var)
{
    char **new_env;
    int i;

    new_env = ft_malloc((len_of_two_d_array(env) + 2) * sizeof(char *));
    i = 0;
    while(*env)
    {
        new_env[i] = ft_strdup(*env);
        i++;
        env++;
    }
    new_env[i++] = ft_strdup(var);
    new_env[i] = NULL;
    return new_env;
}

void sort_env(char **env)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while(env[i])
    {
        j = i + 1;
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
    print_env(env);
} 