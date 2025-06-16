#include "minishell.h"

void update_env_dir(char **env, char *old_dir, char *new_dir)
{
    int i;
    i = 0;
    while(env[i])
    {
        if(ft_strncmp(env[i], "OLDPWD=", 7) == 0)
            env[i] = ft_strdup(ft_strjoin("OLDPWD=", old_dir), 0);
        else if(ft_strncmp(env[i], "PWD=", 4) == 0)
            env[i] = ft_strdup(ft_strjoin("PWD=", new_dir), 0);
        i++;
    }
}

void cd(char **env, char **path, int apply_cd)
{
    char *old_dir;
    char *new_dir;

    if(are_they_equal(*path, "cd"))
        path++;
    old_dir = pwd();
    if(chdir(*path) == 0)
    {
      if(!apply_cd)
        return;
      new_dir = pwd();
      update_env_dir(env, old_dir, new_dir);
    }
    else
    	print_error("%s\n" , strerror(errno));
}
