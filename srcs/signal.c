/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:26:38 by tlaraine          #+#    #+#             */
/*   Updated: 2021/06/05 15:04:15 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint(int sig)
{
	if (g_p->status != 131 && g_p->status != 130)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_putstr_fd(g_p->ps_one, STDOUT_FILENO);
	}
	return ;
}

void	sigstop(int sig)
{
	return ;
}

void	sigquit(int sig)
{
	return ;
}
