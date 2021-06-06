/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:26:38 by tlaraine          #+#    #+#             */
/*   Updated: 2021/06/06 14:31:55 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sigint(int sig)
{
	if (g_p->pid == 0)
	{
		g_p->output = -1;
		if (g_p->res != NULL)
			free(g_p->res);
		g_p->res = NULL;
		g_p->output += t_print("\n");
		g_p->output += t_print(g_p->ps_one);
		g_p->status = 1;
	}
	else
		ft_putstr_fd("\n", STDOUT_FILENO);
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
