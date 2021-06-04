#include "libft.h"

char	*ft_lstgetnum(t_list *lst, int num)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (NULL);
	if (num <= -1)
		return ("");
	while (lst)
	{
		if (i == num)
			return (lst->content);
		lst = lst->next;
		i++;
	}
	return (NULL);
}
