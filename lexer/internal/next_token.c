#include "lexer_internal.h"

static t_token	*redirect_token(t_lexer *l)
{
	t_token	*token;

	token = NULL;
	if (l->ch == '>')
	{
		if (l->input[l->read_position] == '>')
		{
			token = new_token(REDIRECT_APPEND, l, 2, l->position);
			read_char(l);
		}
		else
			token = new_token(REDIRECT_OUT, l, 1, l->position);
	}
	else if (l->ch == '<')
	{
		if (l->input[l->read_position] == '<')
		{
			token = new_token(HEREDOC, l, 2, l->position);
			read_char(l);
		}
		else
			token = new_token(REDIRECT_IN, l, 1, l->position);
	}
	return (token);
}

static t_token	*command_separater_token(t_lexer *l)
{
	t_token	*token;

	token = NULL;
	if (l->ch == '|')
	{
		if (l->input[l->read_position] == '|')
		{
			token = new_token(OR_IF, l, 2, l->position);
			read_char(l);
		}
		else
			token = new_token(PIPE, l, 1, l->position);
	}
	else if (l->ch == '&')
	{
		if (l->input[l->read_position] == '&')
		{
			token = new_token(AND_IF, l, 2, l->position);
			read_char(l);
		}
		else
			token = new_token(ILLEGAL, l, 1, l->position);
	}
	return (token);
}

static t_token	*subeshell_token(t_lexer *l)
{
	t_token	*token;

	token = NULL;
	if (l->ch == '(')
	{
		token = new_token(LPAREN, l, 1, l->position);
		l->is_subshell = true;
	}
	else if (l->ch == ')')
	{
		token = new_token(RPAREN, l, 1, l->position);
		l->is_subshell = false;
	}
	return (token);
}

t_token	*next_token(t_lexer *l)
{
	t_token	*token;

	token = skip_space(l);
	if (token)
		return (token);
	if (l->ch == '>' || l->ch == '<')
		token = redirect_token(l);
	else if (l->ch == '|' || l->ch == '&')
		token = command_separater_token(l);
	else if (l->ch == '(' || l->ch == ')')
		token = subeshell_token(l);
	else if (l->ch == '\0')
		token = new_token(EOL, l, 1, l->position);
	else
	{
		token = new_token_string(l);
		return (token);
	}
	read_char(l);
	return (token);
}
