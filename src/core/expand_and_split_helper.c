#include "minishell.h"

void expand_and_split_helper(t_shell_control_block *sh, int index)
{
	char *ptr;

	ptr = expand_if_possible(sh, sh->splitted[index], 0);
	if (are_they_equal(sh->splitted[index], ptr)) {
		rm_quotes_from_one_str(sh, &ptr);
	add_token_to_lst(&sh->tokenze, new_token(ptr, get_token_type(ptr)));
	}
	else
		split_after_expantion(sh, ptr, sh->splitted[index]);
}
