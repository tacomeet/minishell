#include "builtin.h"

int	builtin_cd(int argc, char **argv, t_env_var **env_vars)
{
	char	*path;

	if (argc == 1)
	{
		path = get_env_value("HOME", *env_vars);
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			return (EXIT_FAILURE);
		}
	}
	else
		path = argv[1];
	if (path[0] == '\0')
		return (EXIT_SUCCESS);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		perror(path);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
