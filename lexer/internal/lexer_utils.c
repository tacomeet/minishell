#include "lexer_internal.h"

void	new_lexer(t_lexer **l, char *input)
{
	*l = x_malloc(sizeof(**l));
	(*l)->input = input;
	(*l)->position = 0;
	(*l)->read_position = 0;
	(*l)->is_subshell = false;
	(*l)->is_redirect = false;
}

void	read_char(t_lexer *l)
{
	if (l->read_position == ft_strlen(l->input))
		l->ch = 0;
	else if (l->read_position > ft_strlen(l->input))
		return ;
	else
		l->ch = l->input[l->read_position];
	l->ch = l->input[l->read_position];
	l->position = l->read_position;
	l->read_position++;
}

t_token	*skip_space(t_lexer *l)
{
	t_token	*token;

	token = NULL;
	while (ft_isspace(l->ch))
	{
		if ((l->is_subshell || l->is_redirect) && l->ch == '\n')
		{
			token = new_token_newline(l);
			if (l->ch == ')')
			{
				free(token);
				token = NULL;
			}
			return (token);
		}
		read_char(l);
	}
	l->is_redirect = false;
	return (token);
}
