/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edebi <edebi@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 01:17:09 by edebi             #+#    #+#             */
/*   Updated: 2020/11/04 15:47:32 by edebi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_len(int n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

int	get_nbr(int n)
{
	if (n > 0)
		return (n);
	else
		return (-n);
}

char	*ft_itoa(int n)
{
	int				len;
	char			*str;
	unsigned int	nbr;

	nbr = get_nbr(n);
	len = count_len(n);
	str = ft_malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	*(str + len--) = '\0';
	while (nbr > 0)
	{
		*(str + len--) = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
	{
		*str = '-';
	}
	if (n == 0)
		*str = '0';
	return (str);
}
