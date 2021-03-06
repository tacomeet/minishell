#ifndef EXECUTE_INTERNAL_H
# define EXECUTE_INTERNAL_H

# include "../../ast/ast.h"
# include "../../env/env.h"

# define CONDITION_AND_IF 0
# define CONDITION_OR_IF 1
# define CONDITION_NL 2

# define READ 0
# define WRITE 1

# define CHILD_PROCESS 0

# define CHILD_PROCESS_NOT_CREATED 0

# define UNSET_FD (-1)

typedef struct s_pipeline		t_pipeline;
typedef struct s_subshell		t_subshell;
typedef struct s_compound_list	t_compound_list;
typedef struct s_simple_command	t_simple_command;

typedef enum e_execute_list_type {
	UNSET,
	T_SIMPLE_COMMAND,
	T_COMPOUND_LIST,
	T_SUBSHELL,
	T_PIPELINE,
}	t_execute_list_type;

typedef enum e_simple_command_err {
	NO_SC_ERR,
	REDIRECT_ERR,
	EXPANSION_ERR,
}	t_simple_command_err;

typedef struct s_executor {
	int			exit_status;
	int			condition;
	t_pipeline	*pipeline;
	t_ast_node	*root;
	t_env_var	**env_vars;
	bool		is_interactive;
}	t_executor;

struct s_pipeline {
	void				*command;
	t_execute_list_type	type;
	t_pipeline			*next;
};

struct s_subshell {
	t_compound_list		*compound_list;
};

struct s_compound_list {
	int				condition;
	t_pipeline		*pipeline;
	t_ast_node		*compound_list_next;
	t_compound_list	*next;
};

struct s_simple_command {
	t_ast_node				*root;
	int						argc;
	char					**argv;
	int						r_out;
	int						r_in;
	t_simple_command_err	err;
};

typedef struct s_exec_pipe_info {
	bool	is_last;
	bool	is_pipe;
	int		pipefd[2];
}	t_exec_pipe_info;

// execute_command_line.c
int		execute_command_line(t_executor *e, t_ast_node *node);

// execute_pipeline.c
int		execute_pipeline(t_executor *e, t_pipeline *c);

// execute_command.c
int		execute_command(t_executor *e,
			   void *command, int type, t_exec_pipe_info *info);

// execute_simple_command.c
int		execute_simple_command(t_executor *e,
			  t_simple_command *sc, t_exec_pipe_info *info);

// execute_utils.c
void	new_executor(t_executor **e, t_env_var **env_vars,
			 t_ast_node *root, bool is_interactive);
void	delete_execute_list(void *element, t_execute_list_type type);
bool	is_execute_condition(int condition, int exit_status);
bool	is_dir(const char *path);

// get_cmd_path.c
bool	get_cmd_path(t_executor *e, char *command, char **path);

// create_envp.c
char	**create_envp(t_executor *e);

#endif //EXECUTE_INTERNAL_H
