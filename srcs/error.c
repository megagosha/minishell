#include "minishell.h"

void	put_error(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
	return ;
}

void	exit_with_error(int error_code)
{
	if (error_code == MEMERROR)
		put_error("Error: ft_malloc failed to allocate memory\n");
	if (error_code == TERM_INIT)
		put_error("Error: termcaps could not be initialized\n");
	exit(1);
}
