#include "minishell.h"

int	skip_before_needle(t_params *p, char **new, char *var, int len)
{
	int	i;

	i = 0;
	while (p->env[i] != NULL)
	{
		if (ft_strncmp(p->env[i], var, len) == 0)
			break ;
		new[i] = p->env[i];
		i++;
	}
	return (i);
}

int	unset_var(char *var, t_params *p)
{
	int		i;
	int		len;
	char	**new;
	int		arr_len;

	arr_len = ft_arrlen(p->env);
	new = ft_malloc(sizeof(char *) * arr_len);
	i = 0;
	len = ft_strlen(var);
	i = skip_before_needle(p, new, var, len);
	if (arr_len == i)
	{
		free(new);
		return (0);
	}
	while (p->env[i + 1] != NULL)
	{
		new[i] = p->env[i + 1];
		i++;
	}
	new[i] = NULL;
	free(p->env);
	p->env = new;
	return (0);
}
