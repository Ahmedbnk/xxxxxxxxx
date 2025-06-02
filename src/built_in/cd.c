#include "minishell.h"

void update_env_dir(char **env, char *old_dir, char *new_dir)
{
    int i;
    i = 0;
    while(env[i])
    {
        if(ft_strncmp(env[i], "OLDPWD=", 7) == 0)
            env[i] = ft_strdup(ft_strjoin("OLDPWD=", old_dir));
        else if(ft_strncmp(env[i], "PWD=", 4) == 0)
            env[i] = ft_strdup(ft_strjoin("PWD=", new_dir));
        i++;
    }
}

void cd(char **env, char *path)
{
    char *old_dir;
    char *new_dir;

    old_dir = pwd();

    printf("old_dir %s\n", old_dir);
    if(chdir(path) == 0)
    {
        new_dir = pwd();
        update_env_dir(env, old_dir, new_dir);
    }
    else
    	printf("%s\n" , strerror(errno));
}
