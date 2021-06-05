#include "libft.h"

void	ft_free_char_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL)
		return ;
	while (arr[i] != NULL)
		free(arr[i++]);
	free(arr);
	return ;
}
