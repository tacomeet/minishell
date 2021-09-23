#include <printf.h>
#include "lexer.h"
#include "../libft/libft.h"

void	read_char(t_lexer *lexer)
{
	if (lexer->read_position == ft_strlen(lexer->input))
		lexer->ch = 0;
	else if (lexer->read_position > ft_strlen(lexer->input))

		return ;
	else
		lexer->ch = lexer->input[lexer->read_position];
	lexer->ch = lexer->input[lexer->read_position];
	lexer->position = lexer->read_position;
	lexer->read_position++;
}

void	skip_space(t_lexer *lexer)
{
	while (ft_isspace(lexer->ch))
		read_char(lexer);
}

t_token	*new_token(t_token_type token_type, t_lexer *lexer, size_t len)
{
	t_token	 *token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = token_type;
	token->literal.start = &lexer->input[lexer->position];
	token->literal.len = len;
	return (token);
}

t_token	*new_token_string(t_lexer *lexer)
{
	t_token	*token;
	char	*str_start;
	size_t	len_start;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	str_start = &(lexer->input[lexer->position]);
	len_start = lexer->position;
	while (!ft_strchr(DELIMITER, lexer->ch))
		read_char(lexer);
	token->type = STRING;
	token->literal.len = lexer->position - len_start;
	token->literal.start = str_start;
	return (token);
}

t_token	*new_token_environment(t_lexer *lexer)
{
	t_token	*token;
	char	*str_start;
	size_t	len_start;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	str_start = &(lexer->input[lexer->position]);
	len_start = lexer->position;
	read_char(lexer);
	while (!ft_strchr(DELIMITER, lexer->ch))
		read_char(lexer);
	token->type = ENVIRONMENT;
	token->literal.len = lexer->position - len_start;
	token->literal.start = str_start;
	return (token);
}