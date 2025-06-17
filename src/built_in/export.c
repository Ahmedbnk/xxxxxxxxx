#include "minishell.h"

static int find_and_update_var(char **env, char *var)
{
    int i;

    i = 0;

    while (env[i])
    {
        if (compare_env_var(env[i], var))
        {
            env[i] = ft_strdup(var, 1);
            return 1;
        }
        i++;
    }
    return 0;
}

static char **add_var_to_env(char **env , char *var)
{
    char **new_env;
    new_env = ft_malloc((len_of_two_d_array(env)+ 2) * sizeof(char *), 1);
    int i;
    i = 0;
    while(*env)
    {
        new_env[i] = ft_strdup(*env, 1);
        i++;
        env++;
    }
    new_env[i++] = ft_strdup(var, 1);
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
        print_env(env);
}

void export(char ***env, char **to_export, t_shell_control_block *shell)
{
    int has_error = 0;
    
    if(!to_export || !*to_export)
    {
        sort_env(*env);
        return ;
    }
    
    while(*to_export)
    {
        // Check if it's a valid variable assignment
        if(!is_valid_var(*to_export) || !is_it_key_value(*to_export))
        {
            has_error = 1;
            // Don't process this argument further
        }
        else
        {
            // Valid variable assignment
            if (find_and_update_var(*env, *to_export))
                ; // Variable updated
            else
                *env = add_var_to_env(*env , *to_export);
        }
        to_export++;
    }
    
    // Set exit status to 1 if there were any errors
    if (has_error)
        shell->exit_status = 1;
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

