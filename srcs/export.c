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

char	**export_split(char *str)
{
	int		i;
	char	**res;
	char	*cpy;

	i = 0;
	cpy = ft_strdup(str);
	res = ft_malloc(sizeof(char *) * 3);
	res[2] = NULL;
	while (cpy[i] != '\0')
	{
		if (cpy[i] == '=')
			break ;
		i++;
	}
	cpy[i] = '\0';
	res[0] = ft_strdup(cpy);
	res[1] = ft_strdup(cpy + i + 1);
	free(cpy);
	return (res);
}

void	free_check_var(char **check_var)
{
	int	i;

	i = 0;
	while (check_var != NULL && check_var[i] != NULL)
	{
		free(check_var[i]);
		i++;
	}
	if (check_var != NULL)
		free(check_var);
}

int	my_export(char **input, t_params *p)
{
	int		i;
	char	**new_var;
	int		j;

	i = ft_arrlen(input);
	if (i <= 1)
		return (1);
	j = 1;
	while (input[j] != NULL)
	{
		new_var = export_split(input[j]);
		if (!check_var(new_var[0]))
			return (write_error("minishell v1: export: `") && write_error
				(input[j]) && write_error("': not a valid identifier\n"));
		else if (get_var_by_name(p->env, new_var[0]) != NULL)
			update_var_by_name(p, new_var[0], new_var[1]);
		else
			add_var(p, new_var[0], new_var[1]);
		free_check_var(new_var);
		j++;
	}
	return (0);
}
