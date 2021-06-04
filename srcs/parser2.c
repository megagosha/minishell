/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:46:57 by tlaraine          #+#    #+#             */
/*   Updated: 2021/05/30 16:09:40 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_quotes(char *line, int *i, char q)
{
	if (*i && line[(*i) - 1] == '\\')
		return ;
	while (line[(*i)++])
	{
		if (line[(*i) - 1] != '\\' && line[*i] == q)
			return ;
	}
}

int	write_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

void	set_new_tok(t_params *params, char *str)
{
	t_tok	*new;
	t_tok	*next;

	new = new_tok(str);
	if (params->tok == NULL)
		params->tok = new;
	else
	{
		next = params->tok;
		while (next->next)
			next = next->next;
		new->prev = next;
		next->next = new;
	}
	set_type(new);
}

int	skipslash(t_params *params, char **line, int *i, int q)
{
	if ((*line)[*i] && (*line)[*i] == '\\' && q && (*line)[(*i) + 1] &&
		!ft_strchr("$\"", (*line)[(*i) + 1]))
		++(params->i) && ++(*i);
	else if ((*line)[*i] && (*line)[*i] == '\\')
	{
		*line = rm_char((*line), *i);
		params->i++;
		if ((*line)[*i])
			++(params->i) && ++(*i);
		if ((*line)[*i] == '\\')
			skipslash(params, line, i, q);
	}
	if (!((*line)[*i]))
		return (0);
	return (1);
}

void	get_quotes(t_params *params, char **line, int *i, char q)
{
	if (q == '\'' || q == '\"')
	{
		*line = rm_char(*line, *i);
		params->i++;
		if (q == '\'')
			while ((*line)[*i] && (*line)[*i] != q)
				++(params->i) && ++(*i);
		else if (q == '\"')
		{
			while ((*line)[*i] && (*line)[*i] != q)
			{
				skipslash(params, line, i, 1);
				if ((*line)[*i] == '$')
				{
					(*line)[*i] = - '$';
					skipslash(params, line, i, 1);
				}
				else if ((*line)[*i] && (*line)[*i] != q)
					++(params->i) && ++(*i);
			}
		}
		++(params->i) && ((*line) = rm_char((*line), (*i)));
	}
	else
		((*line)[*i] = - '$');
}
