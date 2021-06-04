#include "libft.h"

int	ft_strarr_cpy(char ***dest, char **src)
{
	int		i;
	char	**dst;

	dst = *dest;
	i = 0;
	while (src[i] != NULL)
		i++;
	dst = ft_malloc(sizeof(char *) * (i + 1));
	if (dst == NULL)
		return (1);
	i = 0;
	while (src[i] != NULL)
	{
		dst[i] = ft_strdup(src[i]);
		if (dst[i] == NULL)
			return (1);
		i++;
	}
	dst[i] = NULL;
	*dest = dst;
	return (0);
}
