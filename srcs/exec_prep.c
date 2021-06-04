#include "minishell.h"

int	prep(t_pipe *pi)
{
	if (check_sep(g_p->tok))
		return (g_p->status = 258);
	if (sort_rdct(g_p) == -1)
	{
		g_p->status = 1;
		return (1);
	}
	check_env(g_p);
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
	cmd->cmd = NULL;
	cmd->argv = NULL;
	cmd->envp = envp;
}

t_tok	*get_args(t_tok *tok, t_ncmd *cmd)
{
	int		i;
	t_tok	*cp;

	i = count_args(tok);
	cmd->argv = ft_malloc(sizeof(char *) * (i + 2));
	i = 0;
	cp = tok;
	while (cp)
	{
		if (i > 0 && cp->type != ARG)
			break ;
		if (i == 0)
			cmd->cmd = cp->str;
		cmd->argv[i] = cp->str;
		i++;
		if (cp->next == NULL || cp->next->type != ARG)
			break ;
		cp = cp->next;
	}
	cmd->argv[i] = NULL;
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
