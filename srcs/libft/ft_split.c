/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 19:45:54 by edebi             #+#    #+#             */
/*   Updated: 2021/06/06 13:42:07 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**alloc_ptr(char const *s, char c)
{
	size_t	i;
	size_t	k;
	char	**res;

	k = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c && i > 0 && s[i - 1] != c)
			k++;
		i++;
	}
	if (s[i] == '\0' && i > 0 && s[i - 1] != c)
		k++;
	res = (char **)ft_malloc(sizeof(char *) * (k + 1));
	if (res == NULL)
		return ((char **)0);
	res[k] = NULL;
	return (res);
}

static char	**mem_free(char **str, int i)
{
	while (i >= 0)
	{
		free(str[i]);
		i--;
	}
	free(str);
	return ((char **)0);
}

static char	**alloc_str(char **res, char const *s, char c)
{
	int		i;
	int		k;
	int		j;

	j = 0;
	k = 0;
	i = 0;
	while (s[i])
	{
		if ((s[i] == c) && i > 0 && s[i - 1] != c)
		{
			res[k] = malloc(j + 1);
			if (res[k] == NULL)
				return (mem_free(res, k - 1));
			j = 0;
			k++;
		}
		else if (s[i] != c)
			j++;
		i++;
	}
	if (s[i] == '\0' && i > 0 && s[i - 1] != c)
		res[k] = malloc(j + 1);
	return (res);
}

static char	**get_result(char **res, char const *s, char c)
{
	int		i;
	int		k;
	int		j;

	j = 0;
	k = 0;
	i = 0;
	while (s[i] && res[k] != NULL)
	{
		if (s[i] == c && i != 0 && s[i - 1] != c)
		{
			res[k][j] = '\0';
			j = 0;
			k++;
		}
		else if (s[i] != c)
		{
			res[k][j] = s[i];
			j++;
		}
		i++;
		if (s[i] == '\0' && s[i - 1] != c)
			res[k][j] = '\0';
	}
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	**res;

	if (s == NULL)
		return ((char **)0);
	res = alloc_ptr(s, c);
	if (res == NULL)
		return (res);
	res = alloc_str(res, s, c);
	if (res == NULL)
		return (res);
	res = get_result(res, s, c);
	return (res);
}
