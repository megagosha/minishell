#include "../includes/minishell.h"

int	prep(t_pipe *pi)
{
	if (check_sep(g_p->tok))
		return (g_p->status = 258);
	pi->cur_pipe = 0;
	if (g_p->tok == NULL || g_p->tok->str == NULL)
		return (1);
	return (0);
}

t_tok	*skip_redirects(t_tok *tok)
{
	if (tok->next != NULL && is_redirect(tok->next->type))
		tok = tok->next;
	else
		return (tok);
	while (tok)
	{
		if (tok->next == NULL || tok->next->next == NULL
			|| !is_redirect(tok->next->next->type))
			break ;
		tok = tok->next->next;
	}
	return (tok);
}

void	init_cmd(t_ncmd *cmd, char **envp)
{
	if (cmd != NULL && cmd->argv != NULL)
	{
		free(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd != NULL && cmd->cmd_path != NULL)
	{
		free(cmd->cmd_path);
		cmd->cmd_path = NULL;
	}
	if (cmd != NULL)
		cmd->envp = envp;
}

t_tok	*get_args(t_tok *tok, t_ncmd *cmd)
{
	int		i;
	t_tok	*cp;

	i = count_args(tok);
	g_p->cmd->argv = ft_malloc(sizeof(char *) * (i + 2));
	i = 0;
	cp = tok;
	while (cp)
	{
		if (i > 0 && cp->type != ARG)
			break ;
		if (i == 0)
			g_p->cmd->cmd = cp->str;
		g_p->cmd->argv[i] = cp->str;
		i++;
		if (cp->next == NULL || cp->next->type != ARG)
			break ;
		cp = cp->next;
	}
	g_p->cmd->argv[i] = NULL;
	return (cp);
}

int	prepare_command(t_ncmd *res, t_pipe *pi)
{
	g_p->tok = get_args(g_p->tok, res);
	g_p->tok = skip_redirects(g_p->tok);
	res->cmd_path = get_exec_path(g_p, res, g_p->exec_paths);
	if (if_pipe_right(g_p->tok))
	{
		switch_pipe(pi);
		if (pipe(pi->fd[pi->cur_pipe]) == -1)
		{
			print_error("pipe", 0);
			return (1);
		}
	}
	return (0);
}
