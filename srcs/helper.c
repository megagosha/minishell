#include "minishell.h"

void	free_tok(t_tok *tok)
{
	t_tok	*tmp;

	while (tok)
	{
		tmp = tok->next;
		if (tok->prev != NULL)
			tok->prev = NULL;
		if (tok->next != NULL)
			tok->next = NULL;
		free(tok);
		tok = tmp;
	}
}
