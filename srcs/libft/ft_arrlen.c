#include "libft.h"

int 	ft_arrlen(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return (0);
	while (args[i] != NULL)
		i++;
	return (i);
}
