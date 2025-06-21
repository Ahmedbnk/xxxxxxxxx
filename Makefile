NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude 
READLINE = -lreadline

# Source directories
SRC_DIR = src
CORE_DIR = $(SRC_DIR)/core
BUILTINS_DIR = $(SRC_DIR)/builtins
EXECUTION_DIR = $(SRC_DIR)/execution
PARSER_DIR = $(SRC_DIR)/parser
EXPANSION_DIR = $(SRC_DIR)/expansion
ENV_DIR = $(SRC_DIR)/env
UTILS_DIR = $(SRC_DIR)/utils

# Source files
SRCS = $(SRC_DIR)/main.c \
	$(CORE_DIR)/shell.c \
	$(BUILTINS_DIR)/builtin_dispatcher.c \
	$(BUILTINS_DIR)/echo.c \
	$(BUILTINS_DIR)/cd.c \
	$(BUILTINS_DIR)/pwd.c \
	$(BUILTINS_DIR)/env.c \
	$(BUILTINS_DIR)/export.c \
	$(BUILTINS_DIR)/unset.c \
	$(BUILTINS_DIR)/env_validation.c \
	$(BUILTINS_DIR)/ft_strcmp.c \
	$(BUILTINS_DIR)/ft_strncmp.c \
	$(BUILTINS_DIR)/ft_isalpha.c \
	$(BUILTINS_DIR)/ft_isdigit.c \
	$(EXECUTION_DIR)/command_executor.c \
	$(EXECUTION_DIR)/execute_command_line.c \
	$(EXECUTION_DIR)/handle_signals.c \
	$(EXECUTION_DIR)/print_exit_signal_message.c \
	$(EXECUTION_DIR)/handle_redir_in.c \
	$(EXECUTION_DIR)/handle_redir_out.c \
	$(EXECUTION_DIR)/handle_append.c \
	$(EXECUTION_DIR)/handle_heredoc.c \
	$(PARSER_DIR)/tokenizer.c \
	$(PARSER_DIR)/lexer.c \
	$(PARSER_DIR)/file_parser.c \
	$(PARSER_DIR)/split_with_operators.c \
	$(PARSER_DIR)/is_between_quotes.c \
	$(PARSER_DIR)/remove_quotes_from_args.c \
	$(PARSER_DIR)/handle_dollar_with_quotes.c \
	$(PARSER_DIR)/check_input_error.c \
	$(EXPANSION_DIR)/expand_if_possible.c \
	$(EXPANSION_DIR)/should_i_expand.c \
	$(EXPANSION_DIR)/is_expand_separator.c \
	$(EXPANSION_DIR)/new_string_after_expand.c \
	$(EXPANSION_DIR)/ft_get_env_var.c \
	$(EXPANSION_DIR)/expand_outside_dollars.c \
	$(EXPANSION_DIR)/expnad_inside_quote_dollar.c \
	$(ENV_DIR)/copy_env.c \
	$(ENV_DIR)/allocate_and_init_expand_list.c \
	$(UTILS_DIR)/ft_strlen.c \
	$(UTILS_DIR)/ft_strdup.c \
	$(UTILS_DIR)/ft_strchr.c \
	$(UTILS_DIR)/ft_strjoin.c \
	$(UTILS_DIR)/ft_substr.c \
	$(UTILS_DIR)/ft_split.c \
	$(UTILS_DIR)/ft_itoa.c \
	$(UTILS_DIR)/ft_memcpy.c \
	$(UTILS_DIR)/ft_isalnum.c \
	$(UTILS_DIR)/ft_lstnew.c \
	$(UTILS_DIR)/ft_lstadd_back.c \
	$(UTILS_DIR)/ft_lstsize.c \
	$(UTILS_DIR)/garbage_collector.c \
	$(UTILS_DIR)/garbage_collection_lstnew.c \
	$(UTILS_DIR)/get_next_line.c \
	$(UTILS_DIR)/ft_putstr_fd.c \
	$(UTILS_DIR)/print_error.c \
	$(UTILS_DIR)/generate_random_name.c \
	$(UTILS_DIR)/custom_join.c \
	$(UTILS_DIR)/are_they_equal.c \
	$(UTILS_DIR)/is_space.c \
	$(UTILS_DIR)/is_quote.c \
	$(UTILS_DIR)/is_all_spaces.c \
	$(UTILS_DIR)/is_protected.c \
	$(UTILS_DIR)/print_file.c \
	$(UTILS_DIR)/read_file.c \
	$(UTILS_DIR)/print_splitted.c \
	$(UTILS_DIR)/pipe_checker.c \
	$(UTILS_DIR)/array_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /Q $(OBJS) 2>nul || echo "No object files to clean"

fclean: clean
	del $(NAME).exe 2>nul || echo "No executable to clean"

re: fclean all

.PHONY: all clean fclean re
