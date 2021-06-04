#include "minishell.h"

char	*open_file(char *str_to_free, char *file_name, int o_flag,
				   int permissions)
{
	int	res;

	if (permissions != -1)
		res = open(file_name, o_flag, permissions);
	else
		res = open(file_name, o_flag);
	if (res < 0)
	{
		print_error(file_name, 0);
		free(str_to_free);
		return (NULL);
	}
	else
	{
		free(str_to_free);
		return (ft_itoa(res));
	}
}

int	open_redirections(t_tok *tok)
{
	if (is_redirect(tok->type))
	{
		if (tok->type == L_RDCT)
		{
			if (tok->prev != NULL)
				tok->str = open_file(tok->str, tok->next->str, O_RDONLY, -1);
		}
		else
		{
			if (tok->type == DR_RDCT)
				tok->str = open_file(tok->str, tok->next->str, of(1), 0644);
			if (tok->next != NULL)
				if (tok->type == R_RDCT)
					tok->str = open_file(tok->str, tok->next->str, of(2), 0644);
		}
		if (tok->str == NULL)
			return (1);
	}
	return (0);
}

void	check_builin(t_ncmd *res)
{
	if (ft_strncmp(res->argv[0], "cd", 3) == 0)
		g_p->status = my_cd(res->argv, g_p);
	if (ft_strncmp(res->argv[0], "exit", 4) == 0)
		gracefull_exit(g_p);
	if (ft_strncmp(res->argv[0], "export", 6) == 0)
		g_p->status = my_export(res->argv, g_p);
	if (ft_strncmp(res->argv[0], "unset", 5) == 0)
		g_p->status = unset_var(res->argv[1], g_p);
}

int	is_redirect(int i)
{
	return (i == L_RDCT || i == R_RDCT || i == DR_RDCT);
}
