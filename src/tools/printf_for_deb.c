
#include "minishell.h"

static void	ft_putchar(char c)
{
	write(2, &c, 1);
}

static void	ft_putstr(char *str)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}
void s(char *str)
{
  ft_putstr("[");
  ft_putstr(str);
  ft_putstr("]\n");
}
