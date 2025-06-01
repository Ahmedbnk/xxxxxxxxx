NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude 
SRCS = main.c \
	src/env/copy_env.c \
	src/env/allocate_and_init_expand_list.c \
	src/expansion/expand_if_possible.c \
	src/utils/custom_join.c \
	src/expansion/should_i_expand.c \
	src/expansion/is_expand_separator.c \
	src/expansion/new_string_after_expand.c \
	src/parser/check_input_error.c \
	src/parser/remove_quotes_from_args.c \
	src/parser/split_with_operators.c \
	src/parser/make_token.c \
	src/parser/is_between_quotes.c \
	src/parser/customized_split.c \
	src/utils/is_space.c \
	src/utils/are_they_equal.c \
	src/utils/len_of_two_d_array.c \
	src/utils/print_splitted.c \
	src/utils/ft_strchr.c \
	src/utils/get_next_line.c \
	src/signals/handle_signals.c\
	src/utils/ft_isalnum.c\
	src/utils/ft_memcpy.c\
	src/utils/ft_split.c\
	src/utils/ft_strdup.c\
	src/utils/ft_itoa.c\
	src/utils/ft_strjoin.c\
	src/utils/ft_strlen.c\
	src/utils/ft_substr.c\
	src/utils/garbage_collection_lstnew.c\
	src/utils/garbage_collector.c\
	src/utils/ft_lstnew.c\
	src/utils/ft_lstadd_back.c\
	src/parser/parse_tokenized.c\
	src/parser/handle_heredoc.c\
	src/utils/print_file.c\
	src/parser/handle_redir_in.c\
	src/utils/read_file.c\
	src/parser/handle_redir_out.c\
	src/parser/handle_append.c \
	src/execution/execute_command.c \
	src/builtins/builtins.c

OBJS = $(SRCS:.c=.o)

READLINE =-lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) 

fclean: clean
	rm -f $(NAME)


re: fclean all

.PHONY: all clean fclean re
