#include "builtin.h"
#include "../exit_status.h"

int	builtin_exit(t_executor *e, int argc, char **argv, bool is_pipe)
{
	int	exit_status;

	if (e->is_interactive && !is_pipe)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (argc == 1)
		exit_status = e->exit_status;
	else if (!atoi_strict(argv[1], &exit_status))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		exit_status = EXIT_STATUS_OUT_OF_RANGE;
	}
	else if (argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	delete_env_lst(*e->env_vars);
	delete_ast_nodes(e->root, NULL);
	delete_execute_list(e->pipeline, T_PIPELINE);
	free(e);
	exit((unsigned char)exit_status);
}
