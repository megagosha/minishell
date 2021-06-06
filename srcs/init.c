#include "../includes/minishell.h"

char	*get_var_by_name(char **haystack, const char *needle)
{
	int	i;
	int	j;

	i = 0;
	while (haystack[i] != NULL)
	{
		j = 0;
		while (haystack[i][j] != '\0')
		{
			if (needle[j] == '\0' && (haystack[i][j] == '='))
				return (haystack[i] + (j + 1));
			if (haystack[i][j] != needle[j])
				break ;
			j++;
		}
		i++;
	}
	return (NULL);
}

void	update_ps_one(t_params *t)
{
	char	*res;

	res = get_var_by_name(t->env, "PS1");
	if (res == NULL)
		t->ps_one = ft_strdup("minishell v1: ");
	else
		t->ps_one = ft_strdup(res);
}

void	init_more_params(t_params *params)
{
	params->hist = NULL;
	params->check = 0;
	params->output = 0;
	params->hist_pos = -1;
	params->total_hist = 0;
	params->res = NULL;
	g_p->pipe = ft_malloc(sizeof(t_pipe));
	g_p->cmd = ft_malloc(sizeof(t_ncmd));
	g_p->cmd->cmd = NULL;
	g_p->cmd->argv = NULL;
	g_p->cmd->cmd_path = NULL;
	g_p->cmd->envp = g_p->env;
	interrogate_terminal(params->term);
	update_ps_one(params);
	change_term_config();
	g_p->pid = 0;
}

void	init_params(t_params *params, char **envp)
{
	int		res;
	char	*str;

	params->status = 0;
	res = ft_strarr_cpy(&params->env, envp);
	params->i = 0;
	params->new_term = ft_malloc(sizeof(struct termios));
	g_p->old_term = ft_malloc(sizeof(struct termios));
	params->term = ft_malloc(sizeof(t_term));
	params->tok = NULL;
	if (res == 1)
		exit_with_error(MEMERROR);
	init_terminal_data(params);
	params->exec_paths = NULL;
	str = get_var_by_name(params->env, "PATH");
	if (str == NULL)
		params->exec_paths = NULL;
	else
		params->exec_paths = ft_split(str, ':');
	init_more_params(params);
}
