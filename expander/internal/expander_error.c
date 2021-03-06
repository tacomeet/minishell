#include "expander_internal.h"

void	expand_redirect_error(char *original_data, t_expander *e)
{
	if (e->err != NO_ERR)
		free(e->err_data);
	e->err = AMBIGUOUS_REDIRECT_ERR;
	e->err_data = x_strdup(original_data);
}

t_ast_node	*handle_expand_error(t_expander *e)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(e->err_data, STDERR_FILENO);
	ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
	free(e->err_data);
	free(e);
	return (NULL);
}

bool	is_empty_data(t_expander *e, t_ast_node *node, char *original_data)
{
	if (node->data[0] == '\0')
	{
		if (node->type == COMMAND_ARG_NODE)
		{
			free(node->data);
			node->data = NULL;
		}
		else
			expand_redirect_error(original_data, e);
		return (true);
	}
	return (false);
}
