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
    printf("DEBUG: add_var_to_env called with var: '%s'\n", var);
    printf("DEBUG: Current env array length: %d\n", len_of_two_d_array(env));
    
    new_env = ft_malloc((len_of_two_d_array(env)+ 2) * sizeof(char *), 1);
    printf("DEBUG: Allocated new_env at %p\n", (void*)new_env);
    
    int i;
    i = 0;
    while(*env)
    {
        printf("DEBUG: Copying env var %d: '%s'\n", i, *env);
        new_env[i] = ft_strdup(*env, 1);
        i++;
        env++;
    }
    printf("DEBUG: Adding new var: '%s'\n", var);
    new_env[i++] = ft_strdup(var, 1);
    new_env[i] = NULL;
    
    printf("DEBUG: Final env array:\n");
    for (int j = 0; j < i; j++)
    {
        printf("DEBUG:   [%d]: '%s'\n", j, new_env[j]);
    }
    
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

void export(char ***env, char **to_export)
{
    printf("DEBUG: export called\n");
    if(!to_export || !*to_export)
    {
        printf("DEBUG: No variables to export, printing sorted env\n");
        sort_env(*env);
        return ;
    }
    while(*to_export)
    {
        printf("DEBUG: Processing export: '%s'\n", *to_export);
        if(!is_valid_var(*to_export) || !is_it_key_value(*to_export) )
        {
            printf("DEBUG: Invalid variable format\n");
            ;
        }
        else
        {
            printf("DEBUG: Valid variable format\n");
            if (find_and_update_var(*env, *to_export))
            {
                printf("DEBUG: Variable updated in existing env\n");
                ;
            }
            else
            {
                printf("DEBUG: Adding new variable to env\n");
                *env = add_var_to_env(*env , *to_export);
                printf("DEBUG: Environment pointer after add_var_to_env: %p\n", (void*)*env);
            }
        }
        to_export++;
    }
    
    printf("DEBUG: Export completed. Final environment:\n");
    for (int i = 0; (*env)[i]; i++)
    {
        printf("DEBUG:   [%d]: '%s'\n", i, (*env)[i]);
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

