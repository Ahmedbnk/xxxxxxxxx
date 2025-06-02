#include "minishell.h"

void unused_vars(int ac, char **av);
char *ft_readline(void);
void expand_input(char **input);
void parse_and_expand(char *line, char ***splitted, char **env);

int main(int ac, char **av, char **env) {
    char *line;
    char **splitted;
    int status;

    unused_vars(ac, av);
    handle_signals();
    while (1) {
        line = ft_readline();
        if (!line)
            break;  // Exit on EOF (Ctrl+D)
        if (*line)  // Only process non-empty lines
        {
            splitted = NULL;
            parse_and_expand(line, &splitted, env);
            if (splitted)
            {
                if (is_builtin(splitted[0]))
                    execute_builtin(splitted, env);
                else
                {
                    int pid = fork();
                    if (pid == 0)
                    {
                        handle_signals_in_child();
                        execute_command(splitted[0], splitted, env);
                        exit(1);  // Exit with error if command not found
                    }
                    else if (pid > 0)
                        waitpid(pid, &status, 0);
                }
            }
        }
        free(line);
    }
    return (0);
}

void unused_vars(int ac, char **av)
{
    (void)ac;
    (void)av;
}

char *ft_readline(void) {
    char *line;
    char *prompt;

    prompt = "minishell$ ";
    line = readline(prompt);
    if (line && *line)
        add_history(line);
    return (line);
}

void expand_input(char **input) {
  int i;
  i = 0;
  while (input[i]) {
		if(are_they_equal(input[i], "<<"))
			i++;
		else
			input[i] = expand_if_possible(input[i], 0);
    i++;
  }
}

void parse_and_expand(char *line, char ***splitted, char **env)
{
  *splitted = customized_split(line);
  *splitted = split_with_operators(*splitted);
  expand_input(*splitted);

  t_data *tokenized = make_token(*splitted);
  if (tokenized) {
    remove_quotes_from_args(*splitted);
    parse_tokenized(tokenized, env);
  }
}
