#include "minishell.h"

// Move these functions to src/built_in/export_utils.c
static int find_and_update_var(char **env, char *var)
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

static char **add_var_to_env(char **env, char *var)
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

// void print_env(char **env)
// {
//     int i;
//     i = 0;
//     while(env[i])
//     {
//         printf("declare -x ");
//         printf("%s\n", env[i]);
//         i++;
//     }
// }

static void sort_env(char **env)
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

void export(char ***env, char **to_export)
{
    if(!to_export || !*to_export)
    {
        sort_env(*env);
        return;
    }
    while(*to_export)
    {
        if(!is_valid_var(*to_export) || !is_it_key_value(*to_export))
            ;
        else if (find_and_update_var(*env, *to_export))
            ;
        else
            *env = add_var_to_env(*env, *to_export);
        to_export++;
    }
}

// int main(int ac, char **av, char **env)
// {
//     (void )  ac;
//     (void ) av;
//     char *avs[] = {NULL};
//     char **ptr = copy_env(env);
//     export(&ptr, avs);
// 	return 0;
// }

