#include "minishell.h"
#include <stdio.h>

int check_ambiguous_and_syntax(t_token *tokens) {
    int i = 0;
    while (tokens[i].word) {
        if (tokens[i].type == REDIR_OUT || tokens[i].type == REDIR_APPEND || tokens[i].type == REDIR_IN) {
            // If the next token is missing, it's a syntax error
            if (!tokens[i+1].word)
                return (print_error("error near new line \n"), 1);
            // If the next token is EMPTY_REDIR or empty string, it's ambiguous
            if (ft_strlen(tokens[i+1].word) == 0 || are_they_equal(tokens[i+1].word, "EMPTY_REDIR"))
                return 2;
            // If the next token contains spaces, it's ambiguous
            for (int j = 0; tokens[i+1].word[j]; j++)
                if (tokens[i+1].word[j] == ' ')
                    return 2;
        }
        i++;
    }
    return 0;
} 