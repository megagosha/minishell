#include "minishell.h"

void	print_error(char *str, int type)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (type == 0 || type == 2)
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	else if (type == 1)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		g_p->status = 127;
	}
	ft_putstr_fd(" ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	stopped_or_exit(t_ncmd *res, int status)
{
	if (WIFEXITED(status))
	{
		if (res->cmd_path == NULL)
			g_p->status = 127;
		else
			g_p->status = WEXITSTATUS(status);
	}
	else if (WIFSTOPPED(status))
	{
		printf("%s stopped and killed. Continue is not supported\n", res->cmd);
		kill(g_p->pid, SIGINT);
	}
	return ;
}

int	of(int i)
{
	if (i == 1)
		return (O_CREAT | O_APPEND | O_RDWR);
	if (i == 2)
		return (O_CREAT | O_TRUNC | O_WRONLY);
	return (0);
}

int	count_args(t_tok *tok)
{
	int	i;

	i = 0;
	while (tok)
	{
		if (i > 0 && tok->type != ARG)
			break ;
		tok = tok->next;
		i++;
	}
	return (i);
}

void	check_errno_in_child(t_ncmd *res)
{
	if (errno == 13)
	{
		print_error(res->argv[0], 2);
		exit(126);
	}
}
