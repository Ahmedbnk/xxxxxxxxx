#include "minishell.h"

#define  SIZE 4096

char *pwd(char **args)
{
    char *buffer;
    
    // Check if there are any arguments (pwd should not accept any)
    if (args && args[1])
    {
        // Check if it's an option (starts with -)
        if (args[1][0] == '-')
        {
            print_error("pwd: %s: invalid option\n", args[1]);
            return NULL;
        }
        // For any other arguments, just ignore them (bash behavior)
    }
    
    buffer = ft_malloc(SIZE, 1);
    if ((getcwd(buffer, SIZE) == NULL))
    {
       print_error("%s\n", strerror(errno));
       return NULL;
    }
    return buffer;
}
