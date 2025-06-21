#include "minishell.h"

void	ft_init_shell_block(t_shell_control_block *shell, int ac, char **av)
{
	(void)ac;
	(void)av;
	shell->env_cpy = NULL;
	shell->line = NULL;
	shell->splitted = NULL;
	shell->file_name_lst = NULL;
	shell->lst = NULL;
	shell->cmd_and_args = NULL;
	shell->env_of_export = NULL;
	shell->exit_status = 0;
}

char	*ft_readline(t_shell_control_block *shell)
{
	shell->line = readline("\001\033[1;31m\002 Undefined Behavior :\001\033[0m\002");
	if (shell->line && *shell->line)
		add_history(shell->line);
	if (shell->line == NULL)
	{
		free(shell->line);
		free_memory(get_garbage_pointer(1));
		free_memory(get_garbage_pointer(0));
		exit(0);
		return (NULL);
	}
	if (check_error(shell))
		return (NULL);
	return (shell->line);
}

void	expand_and_split(t_shell_control_block *shell)
{
	int		i;
	char	*ptr;

	i = 0;
	shell->lst = NULL;
	while (shell->splitted[i])
	{
		if (are_they_equal(shell->splitted[i], "<<"))
		{
			ft_lstadd_back(&shell->lst, ft_lstnew(shell->splitted[i++]));
			ft_lstadd_back(&shell->lst, ft_lstnew(shell->splitted[i]));
		}
		else
		{
			ptr = expand_if_possible(shell, shell->splitted[i], 0);
			if (are_they_equal(shell->splitted[i], ptr))
			{
				rm_quotes_from_one_str(shell, &ptr);
				ft_lstadd_back(&shell->lst, ft_lstnew(ptr));
			}
			else
				split_after_expantion(shell, ptr, shell->splitted[i]);
		}
		i++;
	}
}

void	split_after_expantion(t_shell_control_block *sh, char *str, char *old_str)
{
	int		i;
	char	**ptr;

	i = 0;
	(void)old_str;
	ptr = customized_split(str);
	while (ptr[i])
	{
		rm_quotes_from_one_str(sh, &ptr[i]);
		ft_lstadd_back(&sh->lst, ft_lstnew(ptr[i]));
		i++;
	}
}

char	**update_splitted(t_shell_control_block *shell)
{
	char	**the_updated_splitted;
	t_list	*ptr;
	int		len;
	int		i;

	len = ft_lstsize(shell->lst);
	the_updated_splitted = ft_malloc((len + 1) * sizeof(char *), 1);
	ptr = shell->lst;
	i = 0;
	while (ptr)
	{
		the_updated_splitted[i++] = (char *)ptr->content;
		ptr = ptr->next;
	}
	the_updated_splitted[i] = NULL;
	return (the_updated_splitted);
}

void	execute_line(t_shell_control_block *shell)
{
	if (shell->tokenized)
	{
		create_all_heredocs(shell);
		get_cmd_and_its_args(shell);
		if (!is_there_a_pipe(shell) && execute_built_in(shell, PARENT))
			;
		else
			execute_command_line(shell);
	}
} 