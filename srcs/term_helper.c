#include "../includes/minishell.h"

int	ft_putc(int c)
{
	char	k;

	k = (unsigned char) c;
	return (write(STDOUT_FILENO, &k, 1));
}

int	t_print(char *str)
{
	ft_putstr_fd(str, STDIN_FILENO);
	return (ft_strlen(str));
}

int	t_print_out(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	return (ft_strlen(str));
}

int	t_printerr(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	return (ft_strlen(str));
}

char	*strcomb(char *str1, const char *str2)
{
	int		len1;
	int		len2;
	char	*res;
	int		i;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	res = ft_malloc(sizeof(char) * (len1 + len2) + 1);
	i = 0;
	while (i < len1)
	{
		res[i] = str1[i];
		i++;
	}
	len1 = 0;
	while (len1 < len2)
	{
		res[i] = str2[len1];
		len1++;
		i++;
	}
	res[i] = '\0';
	if (str1 != NULL)
		free(str1);
	return (res);
}
