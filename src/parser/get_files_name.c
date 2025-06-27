#include "minishell.h"

int is_there_a_char(char *str)
{
	while(*str)
	{
		if(is_space(*str))
			str++;
		else
			return 1;
	}
	return 0;
}

int	is_there_a_space_outside_q(char *str)
{
	if (!str)
		return (0);
	int i;
	i = 0;
	int status;
	status = 0;
	if(!is_there_a_char(str))
		return 1;
	while (str[i])
	{
		if(!is_space(str[i]) && (status ==0 || status==2 ))
			status++;
		else if (is_space(str[i]) && status == 1)
			status++;
		if(status == 3)
			return (1);
		i++;
	}
	return (0);
}

static void	handle_expansion_result(t_shell_control_block *sh,
t_name_lst *ptr, char *str)
{
	(void)sh;
	if (are_they_equal(ptr->file_name, str))
		return ;
	if (is_there_a_space_outside_q(str))
	{
		s(str);
		ptr->status = AMBIGUOUS;
	}
	ptr->file_name = str;
}

void	prepare_lst(t_shell_control_block *sh)
{
	t_name_lst	*ptr;
	char		*str;

	if (!sh || !sh->file_name_lst)
		return ;
	ptr = sh->file_name_lst;
	while (ptr)
	{
		str = expand_if_possible(sh, ptr->file_name, 0);
		if (!str || !*str)
		{
			ptr->status = AMBIGUOUS;
			ptr = ptr->next;
			continue ;
		}
		handle_expansion_result(sh, ptr, str);
		ptr = ptr->next;
	}
}

static void	process_redirection_token(t_shell_control_block *sh, char **ptr)
{
	t_name_lst	*new_node;

	if (!*(ptr + 1))
		return ;
	new_node = new_file_name(*(ptr + 1), VALID);
	if (new_node)
		add_back_file_name(&(sh->file_name_lst), new_node);
}

static void	process_pipe_token(t_shell_control_block *sh)
{
	t_name_lst	*new_node;

	new_node = new_file_name("|", NEW_START);
	if (new_node)
		add_back_file_name(&(sh->file_name_lst), new_node);
}

static void	parse_tokens(t_shell_control_block *sh)
{
	char	**ptr;

	if (!sh || !sh->splitted)
		return ;
	ptr = sh->splitted;
	while (*ptr)
	{
		if (is_redirection(*ptr))
		{
			process_redirection_token(sh, ptr);
			ptr++;
		}
		else if (are_they_equal(*ptr, "|"))
			process_pipe_token(sh);
		ptr++;
	}
}

// static void	debug_print_node(t_name_lst *lst)
// {
// 		printf("------> file name is %s\n", (char *)lst->file_name);
// 		printf("------> valid is %d\n", lst->valid);
// 		printf("------> is new start is %d\n", lst->new_start);
// 		printf("***********************>\n");
// }

// static void	debug_print_list(t_shell_control_block *sh)
// {
// 	t_name_lst	*lst;

// 	if (!sh || !sh->file_name_lst)
// 		return ;
// 	lst = sh->file_name_lst;
// 	while (lst)
// 	{
// 		debug_print_node(lst);
// 		lst = lst->next;
// 	}
// }

void	get_files_name(t_shell_control_block *sh)
{
	if (!sh)
		return ;
	sh->file_name_lst = NULL;
	parse_tokens(sh);
	prepare_lst(sh);
	// debug_print_list(sh);
}
