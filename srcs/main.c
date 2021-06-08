/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:15:40 by edebi             #+#    #+#             */
/*   Updated: 2021/06/08 22:27:20 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_params	*g_p;

char	*check_other_path(t_ncmd *cmd, t_params *p, char **exec_paths)
{
	if (file_exist(cmd->argv[0]) && ft_strchr("./", cmd->argv[0][0]))
		return (free_exec_path(ft_strdup(cmd->argv[0]), exec_paths));
	else
		return (free_exec_path(NULL, exec_paths));
}

int	file_exist(char *filename)
{
	struct stat	buffer;
	int			exist;

	exist = stat(filename, &buffer);
	if (exist == 0)
		return (1);
	else
		return (0);
}

char	*get_exec_path(t_params *p, t_ncmd *cmd, char **exec_paths)
{
	int		i;
	char	*str;
	char	*buf;
	char	*path;

	i = 0;
	if (cmd->argv == NULL || cmd->argv[0] == NULL)
		return (NULL);
	path = get_var_by_name(g_p->env, "PATH");
	exec_paths = ft_split(path, ':');
	while (exec_paths != NULL && exec_paths[i] != NULL)
	{
		str = ft_strjoin(exec_paths[i], "/");
		buf = str;
		str = ft_strjoin(str, cmd->argv[0]);
		if (file_exist(str))
		{
			free(buf);
			return (free_exec_path(str, exec_paths));
		}
		free(buf);
		free(str);
		i++;
	}
	return (check_other_path(cmd, p, exec_paths));
}

int	my_exec(t_params *p)
{
	t_tok	*beg;

	if (prep(g_p->pipe))
		return (EXIT_FAILURE);
	beg = g_p->tok;
	while (g_p->tok)
	{
		check_env(g_p);
		if (sort_rdct(g_p) == -1)
		{
			g_p->status = 1;
			return (1);
		}
		init_cmd(g_p->cmd, p->env);
		if (exec_cmd(g_p->cmd, g_p->pipe))
			return (EXIT_FAILURE);
		g_p->pid = 0;
	}
	free_tok(beg);
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*tmp;

	g_p = malloc(sizeof(t_params));
	signal(SIGINT, &sigint);
	signal(SIGTSTP, &sigstop);
	signal(SIGQUIT, &sigquit);
	init_params(g_p, envp);
	while (get_command(&line, g_p))
	{
		if (line == NULL)
			continue ;
		g_p->tok = NULL;
		tmp = ft_strtrim(line, " ");
		parse(g_p, tmp);
		if (tmp != NULL)
			free(tmp);
		free(line);
		line = NULL;
		tmp = NULL;
	}
	return (0);
}
