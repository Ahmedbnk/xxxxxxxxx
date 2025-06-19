#include "minishell.h"
#include <string.h>

// Helper: is this token a redirection operator?
static int is_redir(const char *s) {
    return are_they_equal(s, ">") || are_they_equal(s, ">>") || are_they_equal(s, "<");
}

// Robust parse_line: tokenize, expand, and keep redir targets as single tokens
void parse_line(t_shell_control_block *shell) {
    char **split = customized_split(shell->line);
    char **with_ops = split_with_operators(split);
    int n = len_of_two_d_array(with_ops);
    t_token *tokens = ft_malloc((n + 1) * sizeof(t_token), 1);
    int i = 0, j = 0;
    while (with_ops[i]) {
        tokens[j].type = get_type_type(with_ops[i]);
        tokens[j].word = NULL;
        // If this is a redirection operator, expand the next token as a single word
        if (is_redir(with_ops[i]) && with_ops[i+1]) {
            tokens[j].word = ft_strdup(with_ops[i], 1);
            j++;
            i++;
            // Expand the next token (redir target) as a single word
            char *expanded = expand_if_possible(shell, with_ops[i], 0);
            tokens[j].type = WORD;
            tokens[j].word = expanded;
        } else {
            // Expand normally
            char *expanded = expand_if_possible(shell, with_ops[i], 0);
            // For non-redir, split on spaces
            char **split_expanded = customized_split(expanded);
            for (int k = 0; split_expanded[k]; k++) {
                tokens[j].type = get_type_type(split_expanded[k]);
                tokens[j].word = ft_strdup(split_expanded[k], 1);
                if (split_expanded[k+1]) j++;
            }
        }
        j++;
        i++;
    }
    tokens[j].word = NULL;
    shell->tokenized = tokens;
} 