#include "libft.h"

int	ft_pos_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	int		k;
	size_t	len_n;

	len_n = ft_strlen(needle);
	if (len_n > len)
		return (-1);
	else
		i = len - len_n + 1;
	k = 0;
	while (i > 0)
	{
		if (ft_strncmp(haystack, needle, len_n))
		{
			k++;
			haystack++;
		}
		else
			return (k);
		i--;
	}
	return (-1);
}

char	*ft_str_replace(const char *string, char *needle, char *replace)
{
	int		s_len;
	int		n_len;
	int		r_len;
	int		n_pos;
	char	*res;

	s_len = ft_strlen(string);
	n_len = ft_strlen(needle);
	r_len = ft_strlen(replace);
	n_pos = ft_pos_strnstr(string, needle, s_len);
	if (n_pos == -1)
		return (NULL);
	res = ft_malloc(sizeof(char) * (s_len - n_len + r_len + 1));
	ft_memcpy(res, string, n_pos + 1);
	ft_memcpy(res + n_pos, replace, r_len);
	ft_memcpy(res + n_pos + r_len, string + n_pos + n_len,
		   s_len - n_len + 1 - n_pos);
	return (res);
}
