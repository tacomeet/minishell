#ifndef LEXER_INTERNAL_H
# define LEXER_INTERNAL_H
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>

# include "../../token/token.h"
# include "../../libft/libft.h"
# include "../../utils/utils.h"
# include "../../wrapper/x.h"

# define DELIMITER "|&<>() \n"

// todo: need to discuss if read_position is actually needed?
// todo: type of positions are different from the book
// position: current character
// read_point: next character
// ch: currently investigated character
typedef struct s_lexer
{
	char	*input;
	size_t	position;
	size_t	read_position;
	char	ch;
	bool	is_subshell;
	bool	is_redirect;
}	t_lexer;

// lexer_utils.c
void	read_char(t_lexer *lexer);
t_token	*skip_space(t_lexer *lexer);
void	new_lexer(t_lexer **l, char *input);

// lexer_new_token.c
t_token	*new_token(t_token_type type, t_lexer *l, size_t len, size_t start);
t_token	*new_token_string(t_lexer *lexer);
t_token	*new_token_newline(t_lexer *lexer);

// next_token.c
t_token	*next_token(t_lexer *l);

#endif
