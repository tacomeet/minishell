#include "execute.h"

bool	new_executor(t_executor **e, t_ast_node *root)
{
	*e = (t_executor *)malloc(sizeof(**e));
	if (!*e)
		return (false);
	(*e)->root = root;
	(*e)->exit_status = EXIT_SUCCESS;
	(*e)->condition = CONDITION_AND_IF;
	(*e)->pipeline = NULL;
	return (true);
}

void	delete_list(void *element, t_list_type type)
{
	if (!element)
		return ;
	if (type == T_REDIRECT_OUT)
	{
		close(((t_redirect_out *)element)->fd);
		delete_list(((t_redirect_out *)element)->next, T_REDIRECT_OUT);
	}
	else if (type == T_REDIRECT_IN)
	{
		close(((t_redirect_in *)element)->fd);
		delete_list(((t_redirect_in *)element)->next, T_REDIRECT_IN);
	}
	else if (type == T_HEREDOC)
		delete_list(((t_heredoc *)element)->next, T_HEREDOC);
	else if (type == T_SIMPLE_COMMAND)
	{
		free(((t_simple_command *)element)->argv);
		delete_list(((t_simple_command *)element)->r_out, T_REDIRECT_OUT);
		delete_list(((t_simple_command *)element)->r_in, T_REDIRECT_IN);
		delete_list(((t_simple_command *)element)->heredoc, T_HEREDOC);
	}
	else if (type == T_PIPELINE)
	{
		delete_list(((t_pipeline *)element)->command, ((t_pipeline *)element)->type);
		delete_list(((t_pipeline *)element)->next, T_PIPELINE);
	}
	free(element);
}

int	ex_perror(t_executor *e, const char *s)
{
	perror(s);
	if (e)
	{
		delete_ast_nodes(e->root, NULL);
		delete_list((void *)e->pipeline, T_PIPELINE);
	}
	return (EXIT_FAILURE);
}

bool	execute_builtin(t_executor *e, int argc, char **argv, bool islast)
{
	if (!ft_strcmp(argv[0], "cd"))
	{
		if (islast)
			e->exit_status = cd(argc, argv);
		else
			cd(argc, argv);
		return (true);
	}
	else if (!ft_strcmp(argv[0], "pwd"))
	{
		if (islast)
			e->exit_status = pwd();
		else
			pwd(argc, argv);
		return (true);
	}
	return (false);
}

bool	is_execute_condition(int condition, int exit_status)
{
	if (condition == CONDITION_AND_IF && exit_status == EXIT_SUCCESS)
		return (true);
	if (condition == CONDITION_OR_IF && exit_status != EXIT_SUCCESS)
		return (true);
	if (condition == CONDITION_NL)
		return (true);
	return (false);
}
