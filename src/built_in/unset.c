#include "minishell.h"

int is_the_var_in_env(char **env, char *var)
{
  while(*env)
  {
    if(compare_env_var(*env, var))
      return 1;
    env++;
  }
  return 0;
}

void remove_var_from_env(char ***env , char *var)
{
  char **env_after_unset;
  int i;
  i = 0;

  env_after_unset = ft_malloc(len_of_two_d_array(*env) * sizeof(char *), 1);
  while(**env)
  {
    if(!compare_env_var(**env, var))
      env_after_unset[i++]=  ft_strdup(**env, 1);
    (*env)++;
  }
  env_after_unset[i] = NULL;
  *env = env_after_unset;
}

int is_valid_unset_var(char *str)
{
    int i;
    i = 0;
    
    if(!str || !*str)
    {
        print_error("unset: `': not a valid identifier\n");
        return 0;
    }
    
    // First character must be a letter or underscore
    if(!ft_isalpha(str[0]) && str[0] != '_')
    {
        print_error("unset: `%s': not a valid identifier\n", str);
        return 0;
    }
    
    while(str[i])
    {
        if(!ft_isalnum(str[i]) && str[i] != '_')
        {
            print_error("unset: `%s': not a valid identifier\n", str);
            return 0;
        }
        i++;
    }
    return 1;
}

void unset(char ***env, char **vars, t_shell_control_block *shell)
{
    int has_error = 0;
    
    while(*vars)
    {
        if(!is_valid_unset_var(*vars))
        {
            has_error = 1;
        }
        else if(is_the_var_in_env(*env, *vars))
        {
            remove_var_from_env(env, *vars);
        }
        vars++;
    }
    
    // Set exit status to 1 if there were any errors
    if (has_error)
        shell->exit_status = 1;
}

// int main(int argc, char *argv[], char *env[])
// {
//   (void ) argv;
//   (void ) argc;
//
//   char **env_cpy = copy_env(env);
//   char *av[] = {"b=1337", "jlj", "z=1337!","13=","a=45", NULL};
//   char *av1[] = {"b=1337", "a", "z=1337!","13=", NULL};
//   printf("%d\n", len_of_two_d_array(env_cpy));
//   export(&env_cpy, av);
//   printf("%d\n", len_of_two_d_array(env_cpy));
//   unset(&env_cpy,  av1);
//   print_env(env_cpy);
//      free_memory(*get_garbage_pointer());
//   return 0;
// }
//
