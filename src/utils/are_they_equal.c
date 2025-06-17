#include "minishell.h"

int	are_they_equal(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if(!str1 || !str2)
		return 0;
	while (str1[i] || str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}
// t_type get_type_type(const char *str) {
//     if (are_they_equal((char *)str, "|"))
//         return (TOKEN_PIPE);
//     else if (are_they_equal((char *)str, "<"))
//         return (TOKEN_REDIR_IN);
//     else if (are_they_equal((char *)str, ">"))
//         return (TOKEN_REDIR_OUT);
//     else if (are_they_equal((char *)str, ">>"))
//         return (TOKEN_REDIR_APPEND);
//     else if (are_they_equal((char *)str, "<<"))
//         return (TOKEN_HEREDOC);
//     // else if (are_they_equal((const char *)str, ""))
//     //     return (TOKEN_EOF);
//     else
//         return (TOKEN_WORD);
// }

// int main()
// {
//     printf("%d\n", get_type_type("<<"));
//     printf("%d\n", get_type_type(">>"));
//     printf("%d\n", get_type_type("<"));
//     printf("%d\n", get_type_type(">"));
//     printf("%d\n", get_type_type("|"));
//     printf("%d\n", get_type_type("kjjhkdfh"));
// }
