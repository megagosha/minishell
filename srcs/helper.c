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

int	check_var(char *new_var)
{
	int	i;

	i = 0;
	while (new_var[i])
	{
		if ((new_var[0] != '_' && !ft_isalpha(new_var[0])))
			return (0);
		else if (i > 0 && new_var[i] != '_' && !ft_isalpha(new_var[i])
			&& !ft_isdigit(new_var[i]))
			return (0);
		i++;
	}
	return (1);
}
