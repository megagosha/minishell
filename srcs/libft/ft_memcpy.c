/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:39:40 by edebi             #+#    #+#             */
/*   Updated: 2021/05/16 14:06:37 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const char	*n_src;
	char		*n_dst;

	if (dst == NULL && src == NULL)
		return (NULL);
	n_src = src;
	n_dst = dst;
	while (n--)
	{
		*n_dst = *n_src;
		n_dst++;
		n_src++;
	}
	return (dst);
}
