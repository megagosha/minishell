#include "../includes/minishell.h"

int 	cd_with_three(char *pwd, char **args, t_params *params)
{
	char	*res;

	res = ft_str_replace(pwd, args[1], args[2]);
	if (chdir(res) == -1)
	{
		t_printerr(strerror(errno));
		t_printerr("\n");
		return (EXIT_FAILURE);
	}
	else
	{
		update_var_by_name(params, "OLDPWD", pwd);
		pwd = get_pwd();
		update_var_by_name(params, "PWD", pwd);
		return (EXIT_SUCCESS);
	}
}

int 	return_error(char *str, char *opt_str)
{
	t_printerr("cd: ");
	t_printerr(str);
	if (opt_str != NULL)
	{
		t_printerr(": ");
		t_printerr(opt_str);
	}
	t_printerr("\n");
	return (EXIT_FAILURE);
}

int 	my_cd(char **args, t_params *params)
{
	char	*pwd;
	int		argc;

	pwd = get_pwd();
	argc = ft_arrlen(args);
	if (argc > 3)
		return (return_error("too many arguments", NULL));
	if (argc == 3)
		cd_with_three(pwd, args, params);
	else if (argc == 2)
	{
		if (chdir(args[1]) == -1)
			return (return_error(strerror(errno), args[1]));
		else
		{
			update_var_by_name(params, "OLDPWD", pwd);
			pwd = get_pwd();
			update_var_by_name(params, "PWD", pwd);
			return (EXIT_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}
