#include "libft.h"

void	*ft_malloc(int size)
{
	void	*res;

	res = malloc(size);
	if (res == NULL)
		exit(0);
	else
		return (res);
}
