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
    char *target_dir;

    if(are_they_equal(*path, "cd"))
        path++;
    
    // Check for too many arguments
    if (path[0] && path[1])
    {
        print_error("cd: too many arguments\n");
        return;
    }
    
    // Determine target directory
    if (!path[0] || are_they_equal(path[0], ""))
    {
        // No argument provided, go to HOME
        target_dir = getenv("HOME");
        if (!target_dir)
        {
            print_error("cd: HOME not set\n");
            return;
        }
    }
    else
    {
        target_dir = path[0];
    }
    
    old_dir = pwd(NULL);
    if(chdir(target_dir) == 0)
    {
      if(!apply_cd)
        return;
      new_dir = pwd(NULL);
      update_env_dir(env, old_dir, new_dir);
    }
    else
    	print_error("cd: %s: %s\n", target_dir, strerror(errno));
}
