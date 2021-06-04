#include "minishell.h"

t_tok	*skip_left(t_tok *tok)
{
	while (tok != NULL)
	{
		if (tok->prev != NULL && tok->prev->prev != NULL
			&& is_redirect(tok->prev->prev->type))
			tok = tok->prev->prev;
		else
			break ;
	}
	if (tok->prev != NULL && is_redirect(tok->type))
		tok = tok->prev;
	return (tok);
}

int	if_pipe_right(t_tok *tok)
{
	if (tok == NULL)
		return (0);
	if (is_redirect(tok->type))
	{
		while (tok != NULL)
		{
			if (tok->next != NULL && tok->next->next != NULL
				&& is_redirect(tok->next->next->type))
				tok = tok->next->next;
			else
				break ;
		}
		if (tok != NULL && is_redirect(tok->type))
			tok = tok->next;
	}
	if (tok != NULL && tok->next != NULL && tok->next->type == PIPE)
		return (1);
	return (0);
}

int	if_pipe_left(t_tok *tok)
{
	if (tok == NULL)
		return (0);
	tok = skip_left(tok);
	while (tok)
	{
		if (tok->type == ARG)
			tok = tok->prev;
		else if (tok->type == CMD)
		{
			if (tok->prev != NULL && tok->prev->type == PIPE)
				return (1);
			else
				return (0);
		}
		else
		{
			printf("Error in if_pipe_left %d\n", tok->type);
			exit(1);
		}
	}
	return (0);
}

void	switch_pipe(t_pipe *p)
{
	int	i;

	i = p->cur_pipe;
	i++;
	if (i > 1)
		p->cur_pipe = 0;
	else
		p->cur_pipe = 1;
	return ;
}
