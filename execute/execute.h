#ifndef MINISHELL_EXECUTE_H
# define MINISHELL_EXECUTE_H

# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>

# include "../ast/ast.h"
# include "../libft/libft.h"

# define SUCCESS 0
# define FAILURE 1

# define CONDITION_AND_IF 0
# define CONDITION_OR_IF 1


# define READ 0
# define WRITE 1

# define CHILD_PROCESS_CREATED 0


typedef struct s_redirect_out	t_redirect_out;
typedef struct s_redirect_in	t_redirect_in;
typedef struct s_heredoc		t_heredoc;
typedef struct s_simple_command	t_simple_command;
typedef struct s_subshell		t_subshell;
typedef struct s_pipeline		t_pipeline;

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

struct s_redirect_out {
	int				fd;
	bool			append;
	t_redirect_out	*next; // maybe there is no need to connect these, just overwrite
};

struct s_redirect_in {
	int				fd;
	t_redirect_in	*next;
};

struct s_heredoc {
	char		*doc;
	t_heredoc	*next;
};

struct s_simple_command {
	t_ast_node			*root;
	int					argc;
	char				**argv;
	t_redirect_out 		*r_out;
	t_redirect_in 		*r_in;
	t_heredoc			*heredoc;
};

struct s_pipeline {
	void		*command;
	t_list_type	type;
	t_pipeline	*next;
};

// execute_init.c
void	execute(t_ast_node *root);

// execute_init_utils.c
bool	new_t_pipeline(t_pipeline **pipeline);
bool	new_t_simple_command(t_simple_command **sc);
bool	new_argv(t_simple_command *sc);


// execute_utils.c
bool	new_executor(t_executor **e, t_ast_node *root);
int		ms_perror(t_executor *e, const char *s);
void	delete_list(void *element, t_list_type type);

// new_redirect.c
bool	new_t_redirect_out(t_redirect_out **r_out, char *filename, bool append);
bool	new_t_redirect_in(t_redirect_in **r_in, char *filename);
bool	new_t_heredoc(t_heredoc **heredoc, char *doc);

// execute_command.c
int		execute_pipeline(t_executor *e, t_pipeline *c);

#endif //MINISHELL_EXECUTE_H