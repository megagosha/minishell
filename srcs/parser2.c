/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:46:57 by tlaraine          #+#    #+#             */
/*   Updated: 2021/06/09 01:02:31 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	quotes(const char *line, int *i, char q)
{
	while (line[(*i)])
	{
		if ((*i) && line[(*i) - 1] && (line[(*i) - 1] != '\\'
				&& line[(*i)] == q))
			return (0);
		(*i)++;
	}
	return (1);
}

int	skip_quotes(char *line, int *i, char q, int c)
{
	int	j;

	if (*i > 0 && line[(*i) - 1] == '\\')
		return (!(++(*i)));
	(*i)++;
	if (q == '\'')
	{
		!(j = 0) && (c = (*i));
		while (line[c])
		{
			if (line[c] == '\'')
				(++j) && ((*i) = c);
			c++;
		}
		if (j)
			return (0);
		return (1);
	}
	return (quotes(line, i, q));
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
			parse_quotes(params, line, i, q);
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
