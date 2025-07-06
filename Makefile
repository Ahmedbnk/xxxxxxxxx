NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude
SRCS = main.c \
	src/env/copy_2d.c \
	src/env/allocate_and_init_expand_list.c \
	src/env/allocat_arr_of_structs_list.c \
	src/env/count_number_of_qute.c \
	src/env/get_start_and_end.c \
	src/env/init_arr_of_structs_list.c \
	src/env/protect_str.c \
	src/error/add_new_line.c \
	src/error/buffering.c \
	src/error/print.c \
	src/execution/check_after_geting_path.c \
	src/execution/check_the_access.c \
	src/execution/cmd_size.c \
	src/execution/execute_command.c \
	src/execution/first_range.c \
	src/execution/ft_getenv.c \
	src/execution/get_cmd_and_its_args.c \
	src/execution/get_path.c \
	src/execution/is_symbole.c \
	src/execution/print_exit_signal_message.c \
	src/execution/second_range.c \
	src/execution/third_range.c \
	src/expansion/expand_if_possible.c \
	src/expansion/expand_and_join_node.c \
	src/expansion/ft_get_env_var.c \
	src/expansion/how_many_dallar_to_expand.c \
	src/expansion/is_expand_separator_fix.c \
	src/expansion/is_expand_separator.c \
	src/expansion/new_string_after_expand.c \
	src/expansion/should_i_expand.c \
	src/expansion/string_after_dollar.c \
	src/expansion/string_before_dollar.c \
	src/expansion/string_to_expand.c \
	src/parser/calculate_all_symboles_operators.c \
	src/parser/check_error.c \
	src/parser/check_unclosed_quotes.c \
	src/parser/create_all_heredocs.c \
	src/parser/customized_split.c \
	src/parser/does_it_has_qoutes.c \
	src/parser/does_string_has_operators.c \
	src/parser/execute_builtin_child.c \
	src/parser/execute_command_line_helper.c \
	src/parser/execute_command_line.c \
	src/parser/ft_w_counter.c \
	src/parser/get_files_name.c \
	src/parser/get_token_type.c \
	src/parser/handle_all_redir.c \
	src/parser/handle_append.c \
	src/parser/handle_dollar_with_quotes.c \
	src/parser/handle_expansion_result.c \
	src/parser/handle_heredoc.c \
	src/parser/handle_redir_in.c \
	src/parser/handle_redir_out.c \
	src/parser/is_between_quotes.c \
	src/parser/is_operator.c \
	src/parser/is_red_symbole.c \
	src/parser/is_there_a_char.c \
	src/parser/is_there_a_space_outside_q.c \
	src/parser/make_token.c \
	src/parser/parse_tokens.c \
	src/parser/prepare_lst.c \
	src/parser/process_command.c \
	src/parser/process_pipe_token.c \
	src/parser/process_redirection_token.c \
	src/parser/read_file.c \
	src/parser/remove_dollar_if_quotes_after_it.c \
	src/parser/remove_quotes_from_args.c \
	src/parser/rm_quotes_from_one_str_helper.c \
	src/parser/skip_ambig_list.c \
	src/parser/skip_command.c \
	src/parser/split_helper.c \
	src/parser/split_string_with_operators.c \
	src/parser/split_with_operators.c \
	src/parser/validate_pipe_syntax.c \
	src/parser/validate_redirection_syntax.c \
	src/signals/handle_signals.c \
	src/signals/handler.c \
	src/tools/printf_for_deb.c \
	src/utils/are_eq.c \
	src/utils/custom_join.c \
	src/utils/fill_n_str.c \
	src/utils/ft_isalnum.c \
	src/utils/ft_itoa.c \
	src/utils/ft_lstadd_back.c \
	src/utils/ft_lstnew.c \
	src/utils/ft_lstsize.c \
	src/utils/ft_memcpy.c \
	src/utils/ft_putstr_fd.c \
	src/utils/ft_split.c \
	src/utils/ft_strchr.c \
	src/utils/ft_strcpy.c \
	src/utils/ft_strdup.c \
	src/utils/ft_strjoin.c \
	src/utils/ft_strlen.c \
	src/utils/ft_substr.c \
	src/utils/ft_w_counter_split.c \
	src/utils/garbage_collection_lstnew.c \
	src/utils/garbage_collector.c \
	src/utils/generate_random_name.c \
	src/utils/get_next_line.c \
	src/utils/get_shell_pointer.c \
	src/utils/is_all_spaces.c \
	src/utils/is_dollar.c \
	src/utils/is_pipe.c \
	src/utils/is_protected.c \
	src/utils/is_quote.c \
	src/utils/is_redirection.c \
	src/utils/is_space.c \
	src/utils/it_there_a_pipe.c \
	src/utils/len_of_two_d_array.c \
	src/utils/lst_file_name_func.c \
	src/utils/n_counter.c \
	src/utils/print_file.c \
	src/utils/print_splitted.c \
	src/utils/read_file.c \
	src/built_in/add_var_to_env.c \
	src/built_in/advance_file_name_list.c \
	src/built_in/cd.c \
	src/built_in/check_ambiguous_redirection.c \
	src/built_in/compare_env_var.c \
	src/built_in/echo.c \
	src/built_in/env.c \
	src/built_in/execute_builtin.c \
	src/built_in/execute_parent_builtin.c \
	src/built_in/export.c \
	src/built_in/find_and_update_var.c \
	src/built_in/ft_isalpha.c \
	src/built_in/ft_isdigit.c \
	src/built_in/ft_strcmp.c \
	src/built_in/ft_strncmp.c \
	src/built_in/init_redirection_vars.c \
	src/built_in/is_builtin.c \
	src/built_in/is_it_key_value.c \
	src/built_in/is_the_var_in_env.c \
	src/built_in/is_valid_flag.c \
	src/built_in/is_valid_var.c \
	src/built_in/parse_redirections.c \
	src/built_in/process_redirection_tokens.c \
	src/built_in/pwd.c \
	src/built_in/remove_var_from_env.c \
	src/built_in/restore_original_fds.c \
	src/built_in/save_original_fds.c \
	src/built_in/setup_input_redirection.c \
	src/built_in/setup_output_redirection.c \
	src/built_in/sort_env.c \
	src/built_in/unset.c \
	src/built_in/update_env_dir.c \
	src/core/execute_line.c \
	src/core/expand_and_split_helper.c \
	src/core/expand_and_split.c \
	src/core/ft_init_shell_block.c \
	src/core/ft_readline.c \
	src/core/is_it_valid_dollar.c \
	src/core/is_out_dollar.c \
	src/core/is_there_invalid_expantion.c \
	src/core/parse_line.c \
	src/core/split_after_expantion.c\
	src/execution/ft_close.c\
	src/utils/ft_atol.c \
	src/utils/check_is_valid_number.c\
	src/built_in/my_exit.c\
	src/utils/set_handler_state.c\
	src/utils/get_fd_pointer.c\
	src/utils/ft_open.c\
	src/utils/free_fd_lst.c\
	src/utils/ft_dup.c\
	src/utils/find_fd_in_lst.c\
	src/utils/ft_pipe.c\

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
