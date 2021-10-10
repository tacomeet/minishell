#ifndef MINISHELL_EXECUTE_H
# define MINISHELL_EXECUTE_H

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>

# include "../ast/ast.h"
# include "../libft/libft.h"
# include "../builtin/builtin.h"

# define CONDITION_AND_IF 0
# define CONDITION_OR_IF 1
# define CONDITION_NL 2

# define NOTFOUND 126
# define INEXECUTABLE 127

# define READ 0
# define WRITE 1

# define CHILD_PROCESS 0

# define CHILD_PROCESS_NOT_CREATED 0
# define NOT_LAST_COMMAND 0

typedef struct s_pipeline		t_pipeline;
typedef struct s_subshell		t_subshell;
typedef struct s_compound_list	t_compound_list;
typedef struct s_simple_command	t_simple_command;
typedef struct s_redirect_out	t_redirect_out;
typedef struct s_redirect_in	t_redirect_in;

typedef enum e_list_type {
	UNSET,
	T_REDIRECT_OUT,
	T_REDIRECT_IN,
	T_HEREDOC,
	T_SIMPLE_COMMAND,
	T_SUBSHELL,
	T_PIPELINE,
}	t_list_type;

typedef struct s_executor {
	t_ast_node	*root; // for free()
	int			exit_status;
	int			condition;
	t_pipeline 	*pipeline;
}	t_executor;

struct s_pipeline {
	void		*command;
	t_list_type	type;
	t_pipeline	*next;
};

struct s_subshell {
	t_compound_list		*compound_list;
	// redirect list
	t_redirect_out 		*r_out;
	t_redirect_in 		*r_in;
};

struct s_compound_list {
	int			exit_status;
	int			condition;
	t_pipeline 	*pipeline;
	t_ast_node	*compound_list_next;
};

struct s_simple_command {
	t_ast_node			*root;
	int					argc;
	char				**argv;
	t_redirect_out 		*r_out;
	t_redirect_in 		*r_in;
};

struct s_redirect_out {
	int				fd;
	t_redirect_out	*next; // maybe there is no need to connect these, just overwrite
};

struct s_redirect_in {
	int				fd;
	t_list_type		type;
	char			*delim;
	t_redirect_in	*next;
};

// execute_init.c
int		execute(t_ast_node *root);
t_compound_list *init_compound_list(t_executor *e, t_ast_node *node);
// execute_init_utils.c
bool	new_t_pipeline(t_pipeline **pipeline);
bool	new_t_subshell(t_subshell **ss);
bool	new_t_compound_list(t_compound_list **cl);
bool	new_t_simple_command(t_simple_command **sc);
bool	new_argv(t_simple_command *sc);


// execute_utils.c
bool	new_executor(t_executor **e, t_ast_node *root);
int		ex_perror(t_executor *e, const char *s);
void	delete_list(void *element, t_list_type type);
bool	execute_builtin(t_executor *e, int argc, char **argv, bool islast);
bool	is_execute_condition(int condition, int exit_status);
void	execute_redirect(t_executor *e, t_simple_command *sc, int orig_stdfd[]);

// new_redirect.c
bool	new_t_redirect_out(t_redirect_out **r_out, char *filename, t_node_type type);
bool	new_t_redirect_in(t_redirect_in **r_in, char *data, t_node_type type);

// execute_command.c
int		execute_pipeline(t_executor *e, t_pipeline *c);

#endif //MINISHELL_EXECUTE_H
