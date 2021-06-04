#include "../includes/minishell.h"

int	my_echo(char **input)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (input[1] && ft_strncmp(input[1], "-n", 2) == 0)
		++n && i++;
	i++;
	while (input[i] != NULL)
	{
		ft_putstr_fd(input[i], STDOUT_FILENO);
		i++;
		if (input[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!n)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
