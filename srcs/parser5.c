/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:46:57 by tlaraine          #+#    #+#             */
/*   Updated: 2021/05/30 18:10:19 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_status(t_params *params, char **line, int *i)
{
	char	*str;
	char	*tmp;
	char	*status;
	int		k;

	tmp = ft_strdup((*line) + (*i) + 2);
	(*line)[*i] = '\0';
	k = 0;
	status = ft_itoa(params->status);
	k = ft_strlen(status);
	*line = strjoinf(*line, status);
	*line = strjoinf(*line, tmp);
	free(status);
	free(tmp);
	return ((*i) += k);
}

void	check_env(t_params *params)
{
	t_tok	*tok;
	int		i;

	tok = params->tok;
	while (tok)
	{
		i = 0;
		while ((tok->str)[i])
		{
			if (((tok->str)[i]) == - '$' && ((tok->str)[i + 1])
				&& ((tok->str)[i + 1]) == '?')
				get_status(params, &(tok->str), &i);
			else if (((tok->str)[i]) == - '$')
				get_env(params, &(tok->str), &i);
			else
				i++;
		}
		tok = tok->next;
	}
}
