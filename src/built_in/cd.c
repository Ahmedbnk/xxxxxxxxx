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

char *get_current_dir()
{
    char *buffer;
    buffer = ft_malloc(4096, 1);
    if ((getcwd(buffer, 4096) == NULL))
    {
       return NULL;
    }
    return buffer;
}

int cd(char **env, char **path)
{
    char *old_dir;
    char *new_dir;

    if(are_they_equal(*path, "cd"))
        path++;
    old_dir = get_current_dir();
    if(chdir(*path) == 0)
    {
        new_dir = get_current_dir();
        update_env_dir(env, old_dir, new_dir);
        return 0;
    }
    else
    {
    	printf("%s\n" , strerror(errno));
        return 1;
    }
}
