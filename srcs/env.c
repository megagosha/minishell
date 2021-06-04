#include "../includes/minishell.h"

void	ft_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
}

void	add_var(t_params *p, char *new_var, char *value)
{
	int		i;
	char	**new;
	char	*tmp;

	i = ft_arrlen(p->env);
	tmp = ft_strjoin(new_var, "=");
	new = ft_malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (p->env[i] != NULL)
	{
		new[i] = p->env[i];
		i++;
	}
	new[i] = ft_strjoin(tmp, value);
	free(tmp);
	new[i + 1] = NULL;
	free(p->env);
	p->env = new;
	return ;
}
