#include "minishell.h"

#define  SIZE 4096

int pwd()
{
    char *buffer;

    buffer = ft_malloc(SIZE, 1);
    if ((getcwd(buffer, SIZE) == NULL))
    {
       printf("%s\n", strerror(errno));
       return 1;
    }
    printf("%s\n", buffer);
    return 0;
}
