/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 15:31:36 by tlaraine          #+#    #+#             */
/*   Updated: 2021/05/30 19:03:17 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_quotes(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			skip_quotes(line, &i, line[i]);
			if (!line[i])
				return (write_error("bash: syntax error open quotes\n"));
		}
		i++;
	}
	return (0);
}

int	skipspace(t_params *params, char *line)
{
	int	*i;

	i = &(params->i);
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	if (!line[*i])
		return (0);
	return (1);
}

void	get_sep(t_params *params, char *line)
{
	char	*str;
	int		k;
	int		*i;

	i = &(params->i);
	if (*i && line[(*i) - 1] == '\\')
		return ;
	if (ft_strchr("<>|;", line[*i]))
	{
		str = ft_strdup(line + (*i));
		k = 0;
		if ((str[k] == '>') && str[k + 1] && str[k + 1] == '>')
			k++;
		str[++k] = '\0';
		set_new_tok(params, str);
		free (str);
		(*i) += k;
	}
}

void	get_new_tok(t_params *params, char *line)
{
	char	*str;
	int		*i;
	int		k;

	i = &(params->i);
	if (line[*i] && !ft_strchr(";<>| ", line[*i]))
	{
		str = ft_strdup(line + (*i));
		k = 0;
		while (str[k] && !ft_strchr(";<>| ", str[k]))
		{
			if (str[k] == '\\')
				skipslash(params, &str, &k, 0);
			if (str[k] == '\'' || str[k] == '\"' || str[k] == '$')
			{
				get_quotes(params, &str, &k, str[k]);
				skipslash(params, &str, &k, 0);
			}
			else
				++(params->i) && (++k);
		}
		str[k] = '\0';
		set_new_tok(params, str);
		free(str);
	}
}

int	parse(t_params *params, char *line)
{
	t_tok	*tok;

	if (!line)
		return (1);
	if (check_quotes(line))
		return (1);
	params->i = 0;
	while (line[params->i])
	{
		skipspace(params, line);
		get_sep(params, line);
		get_new_tok(params, line);
	}
	return (my_exec(params));
}
