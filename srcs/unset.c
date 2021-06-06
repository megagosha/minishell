#include "minishell.h"

int	compare(char *env, char **var)
{
	int	i;

	i = 1;
	while (var[i])
	{
		if (ft_strncmp(env, var[i], ft_strlen(var[i])) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

int	unset_var(char **var, t_params *p)
{
	int		i;
	int		j;
	char	**new;

	j = 0;
	i = 0;
	new = malloc(sizeof(char *) * (ft_arrlen(p->env) + 1));
	while (p->env[i])
	{
		if (compare(p->env[i], var) >= 0)
		{
			free(p->env[i]);
			i++;
			continue ;
		}
		new[j] = p->env[i];
		j++;
		i++;
	}
	new[j] = NULL;
	free(p->env);
	g_p->env = new;
	return (1);
}
