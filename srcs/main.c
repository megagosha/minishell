/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlaraine <tlaraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:15:40 by edebi             #+#    #+#             */
/*   Updated: 2021/05/30 18:15:29 by tlaraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_params	*g_p;

char	*check_other_path(t_ncmd *cmd, t_params *p, char **exec_paths)
{
	if (file_exist(cmd->argv[0]) && ft_strchr("./", cmd->argv[0][0]))
		return (cmd->argv[0]);
	else
		return (NULL);
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
			return (str);
		}
		free(buf);
		free(str);
		i++;
	}
	return (check_other_path(cmd, p, exec_paths));
}

int	my_exec(t_params *p)
{
	t_ncmd	*res;
	t_pipe	*pi;

	pi = ft_malloc(sizeof(t_pipe));
	res = ft_malloc(sizeof(t_ncmd));
	if (prep(pi))
		return (EXIT_FAILURE);
	while (g_p->tok)
	{
		init_cmd(res, p->env);
		if (exec_cmd(res, pi))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;

	g_p = malloc(sizeof(t_params));
	signal(SIGINT, &sigint);
	signal(SIGTSTP, &sigstop);
	signal(SIGQUIT, &sigquit);
	init_params(g_p, envp);
	while (get_command(&line, g_p))
	{
		g_p->tok = NULL;
		parse(g_p, ft_strtrim(line, " "));
		free(line);
		line = NULL;
		free_tok(g_p->tok);
	}
	return (0);
}
