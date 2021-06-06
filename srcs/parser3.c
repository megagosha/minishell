/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:46:57 by tlaraine          #+#    #+#             */
/*   Updated: 2021/05/30 18:59:36 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_pipe(int i)
{
	return (i >= SEMIC && i <= PIPE);
}

t_tok	*new_tok(char *str)
{
	t_tok	*tok;

	tok = ft_malloc(sizeof(t_tok));
	tok->str = ft_strdup(str);
	tok->next = NULL;
	tok->prev = NULL;
	return (tok);
}

void	set_type(t_tok *tok)
{
	if (!ft_strncmp(tok->str, "", 1))
		tok->type = EMPTY;
	else if (!ft_strncmp(tok->str, "<", 1))
		tok->type = L_RDCT;
	else if (!ft_strncmp(tok->str, ">>", 2))
		tok->type = DR_RDCT;
	else if (!ft_strncmp(tok->str, ">", 1))
		tok->type = R_RDCT;
	else if (!ft_strncmp(tok->str, ";", 1))
		tok->type = SEMIC;
	else if (!ft_strncmp(tok->str, "|", 1))
		tok->type = PIPE;
	else if (!tok->prev || tok->prev->type >= L_RDCT)
		tok->type = CMD;
	else
		tok->type = ARG;
}

char	*rm_char(char *line, int i)
{
	char	*new;
	char	*tmp;

	new = ft_strdup(line);
	new[i] = '\0';
	tmp = new;
	new = ft_strjoin(new, line + i + 1);
	free(tmp);
	free(line);
	return (new);
}

int	check_sep(t_tok *tok)
{
	while (tok)
	{
		if (is_redirect(tok->type) && (!tok->next
				|| (tok->next->type >= L_RDCT && tok->next->type <= PIPE)))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			if (tok->next)
				ft_putstr_fd(tok->next->str, 2);
			else
				ft_putstr_fd("newline", 2);
			ft_putstr_fd("'\n", 2);
			return (258);
		}
		if (is_pipe(tok->type) && (!tok->prev || !tok->next
				|| (tok->prev->type >= L_RDCT && tok->prev->type <= PIPE)))
		{
			ft_putstr_fd("bash: syntax error near unexpected token `", 2);
			ft_putstr_fd(tok->str, 2);
			ft_putstr_fd("\'\n", 2);
			return (258);
		}
		tok = tok->next;
	}
	return (0);
}
