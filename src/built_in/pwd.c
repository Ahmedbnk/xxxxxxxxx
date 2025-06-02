#include "minishell.h"

#define  SIZE 4096

char *pwd()
{
    char *buffer;

    buffer = ft_malloc(SIZE);
    if ((getcwd(buffer, SIZE) == NULL))
    {
       printf("%s\n", strerror(errno));
       return NULL;
    }
    return buffer;
}
