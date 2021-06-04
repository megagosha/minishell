#include "../includes/minishell.h"

/*
//1. open all fds
//2. prepare command with args
//3. look for redirect
//4. if redirect skip redirect to next command or pipe
//5. fork
//6. in fork check for redirect
//7. if redirect dup2 redirect to in or out.
//8. if redirect in pipe connect to pipe. */

int	check_parent(t_ncmd *res, int status, int wait_res, int pid)
{
	if (wait_res == -1)
	{
		print_error("waitpid", 0);
		return (EXIT_FAILURE);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
		{
			printf("Quit: %d\n", WTERMSIG(status));
			g_p->status = 131;
		}
		else if (WTERMSIG(status) == SIGINT)
			g_p->status = 130;
		else
			g_p->status = WTERMSIG(status);
	}
	else
		stopped_or_exit(res, status, pid);
	return (0);
}

void	check_child(t_ncmd *res)
{
	if (ft_strncmp(res->argv[0], "echo", 5) == 0)
	{
		my_echo(res->argv);
		exit(EXIT_SUCCESS);
	}
	if (ft_strncmp(res->argv[0], "cd", 3) == 0)
		exit(EXIT_SUCCESS);
	if (ft_strncmp(res->argv[0], "exit", 4) == 0)
		exit(EXIT_SUCCESS);
	if (ft_strncmp(res->argv[0], "export", 6) == 0)
		exit(EXIT_SUCCESS);
	if (ft_strncmp(res->argv[0], "unset", 5) == 0)
		exit(EXIT_SUCCESS);
	if (ft_strncmp(res->argv[0], "env", 3) == 0)
	{
		ft_env(g_p->env);
		exit(EXIT_SUCCESS);
	}
	if (res->cmd_path == NULL)
	{
		g_p->status = 127;
		print_error(res->argv[0], 1);
		exit(EXIT_FAILURE);
	}
}

void	if_parent(t_pipe *pi, pid_t pid, t_ncmd *res)
{
	int	wait_res;
	int	status;

	wait_res = waitpid(pid, &status, WUNTRACED);
	change_term_config();
	check_parent(res, status, wait_res, pid);
	check_builin(res);
	if (if_pipe_left(g_p->tok))
	{
		if (if_pipe_right(g_p->tok))
			switch_pipe(pi);
		close(pi->fd[pi->cur_pipe][0]);
		switch_pipe(pi);
	}
	if (g_p->tok->type == R_RDCT || g_p->tok->type == DR_RDCT)
		close(ft_atoi(g_p->tok->str));
	if (g_p->tok->type == L_RDCT)
		close(ft_atoi(g_p->tok->str));
	if (if_pipe_right(g_p->tok))
		close(pi->fd[pi->cur_pipe][1]);
}

void	if_child(t_pipe *pi, t_ncmd *res)
{
	if (g_p->tok->type == L_RDCT)
		dup2(ft_atoi(g_p->tok->str), STDIN_FILENO);
	else if (if_pipe_left(g_p->tok))
	{
		if (if_pipe_right(g_p->tok))
			switch_pipe(pi);
		dup2(pi->fd[pi->cur_pipe][0], STDIN_FILENO);
		close(pi->fd[pi->cur_pipe][0]);
	}
	if (g_p->tok->type == R_RDCT || g_p->tok->type == DR_RDCT)
		dup2(ft_atoi(g_p->tok->str), STDOUT_FILENO);
	else if (if_pipe_right(g_p->tok))
	{
		if (if_pipe_left(g_p->tok))
			switch_pipe(pi);
		dup2(pi->fd[pi->cur_pipe][1], STDOUT_FILENO);
		close(pi->fd[pi->cur_pipe][0]);
		close(pi->fd[pi->cur_pipe][1]);
	}
	check_child(res);
	execve(res->cmd_path, res->argv, res->envp);
	check_errno_in_child(res);
	exit(EXIT_FAILURE);
}

int	exec_cmd(t_ncmd *res, t_pipe *pi)
{
	pid_t	pid;

	if (g_p->tok->type == CMD && (g_p->tok->prev == NULL
			|| !is_redirect(g_p->tok->prev->type)))
	{
		if (prepare_command(res, pi))
			return (EXIT_FAILURE);
		pid = fork();
		default_terminal();
		if (pid < 0)
			exit(EXIT_FAILURE);
		else if (pid == 0)
			if_child(pi, res);
		else if (pid > 0)
			if_parent(pi, pid, res);
	}
	if (g_p->tok != NULL)
	{
		if (g_p->tok->next == NULL)
			close_fd(g_p->tok);
		g_p->tok = g_p->tok->next;
	}
	return (EXIT_SUCCESS);
}
