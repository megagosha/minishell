/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:46:57 by tlaraine          #+#    #+#             */
/*   Updated: 2021/06/08 22:22:56 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char 	*strjoinf(char *str1, char *str2)
{
	char	*tmp;

	if (str2)
	{
		tmp = str1;
		str1 = ft_strjoin(str1, str2);
		free(tmp);
	}
	return (str1);
}

void	sort_swap(t_params *params, t_tok *rdct, t_tok *tok)
{
	rdct->prev->next = rdct->next;
	if (rdct->next)
		rdct->next->prev = rdct->prev;
	rdct->next = tok;
	if (tok->prev)
	{
		tok->prev->next = rdct;
		rdct->prev = tok->prev;
		tok->prev = rdct;
	}
	else
	{
		params->tok = rdct;
		tok->prev = rdct;
	}
}

int	close_fd(t_tok *rdct)
{
	int	fd;

	while (rdct)
	{
		if (is_redirect(rdct->type))
		{
			if (rdct->next != NULL && rdct->next->str != NULL)
			{
				fd = ft_atoi(rdct->str);
				if (fd > 0)
					close(fd);
			}
		}
		rdct = rdct->prev;
	}
	return (-1);
}

int	sort_rdct(t_params *params)
{
	t_tok	*tok;
	t_tok	*rdct;

	tok = params->tok;
	while (tok && tok->type != SEMIC)
	{
		if (is_redirect(tok->type))
		{
			rdct = tok;
			while (rdct && rdct->type < SEMIC)
			{
				if (is_redirect(rdct->type))
					if (open_redirections(rdct))
						return (close_fd(rdct));
				if (rdct->type == ARG)
					sort_swap(params, rdct, tok);
				rdct = rdct->next;
			}
			if (rdct)
				tok = rdct;
		}
		tok = tok->next;
	}
	return (0);
}

int	get_env(t_params *params, char **line, int *i)
{
	char	*env;
	char	*tmp;
	int		k;

	if (!((*line)[(*i) + 1]) || ((*line)[(*i) + 1] &&
		(*line)[(*i) + 1] != '_' && !ft_isalnum((*line)[(*i) + 1])))
		return ((*line)[(*i)++] = '$');
	env = ft_strdup((*line) + (*i) + 1);
	(*line)[*i] = '\0';
	k = 0;
	while (env[k] && (env[k] == '_' || ft_isalnum(env[k])))
		k++;
	env[k] = '\0';
	tmp = env;
	env = get_var_by_name(params->env, env);
	free(tmp);
	tmp = ft_strdup((*line) + (*i) + 1 + k);
	if (env && ft_strlen(env) > k)
		k = ft_strlen(env);
	else if (!env)
		k = 0;
	*line = strjoinf(*line, env);
	*line = strjoinf(*line, tmp);
	free(tmp);
	return ((*i) += k);
}
