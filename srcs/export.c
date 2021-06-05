#include "../includes/minishell.h"

void	update(t_params *p, char *str, int i, char **env)
{
	char	*tmp;

	tmp = env[i];
	env[i] = str;
	free(tmp);
	p->env = env;
	return ;
}

void	update_var_by_name(t_params *p, char *new_var, char *value)
{
	int		i;
	char	*str;
	char	*tmp;
	char	**env;

	i = 0;
	str = ft_strjoin(new_var, "=");
	tmp = str;
	str = ft_strjoin(str, value);
	free(tmp);
	env = p->env;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], new_var, ft_strlen(new_var)) == 0)
			return (update(p, str, i, env));
		i++;
	}
	free(str);
	return ;
}

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

int	my_export(char **input, t_params *p)
{
	int		i;
	char	**new_var;

	i = ft_arrlen(input);
	if (i >= 1)
		new_var = ft_split(input[1], '=');
	else
		return (0);
	if (ft_arrlen(new_var) >= 2)
	{
		if (!check_var(new_var[0]))
			return (write_error("minishell v1: export: `") && write_error
				(input[1]) && write_error("': not a valid identifier\n"));
		else if (get_var_by_name(p->env, new_var[0]) != NULL)
			update_var_by_name(p, new_var[0], new_var[1]);
		else
			add_var(p, new_var[0], new_var[1]);
		return (0);
	}
	else
		return (1);
}
