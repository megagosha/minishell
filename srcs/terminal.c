#include "../includes/minishell.h"

int	check_input(char **line, t_params *t)
{
	if (ft_strncmp(t->buf, "\n", t->ch_read + 1) == 0)
		return (1);
	return (0);
}

int	check_keys(t_params *t)
{
	if (ft_strncmp(t->buf, "\x7f", t->ch_read + 1) == 0)
	{
		t->output += delete_char(t->term, t->res, t->output, t->ps_one);
		return (1);
	}
	if (ft_strncmp(t->term->ku, t->buf, t->ch_read + 1) == 0)
	{
		ft_key(1);
		return (1);
	}
	else if (ft_memcmp(t->buf, t->term->kd, t->ch_read + 1) == 0)
	{
		ft_key(-1);
		return (1);
	}
	else if (ft_memcmp(t->buf, t->term->kr, t->ch_read + 1) == 0
		|| ft_memcmp(t->buf, t->term->kl, t->ch_read + 1) == 0
		|| ft_memcmp(t->buf, "\t", 1) == 0)
	{
		t_print(t->term->sound);
		return (1);
	}
	return (0);
}

int	check_exit(const char *buf, const char *str, t_params *t)
{
	if ((buf != NULL && buf[0] == 4) && (str != NULL && str[0] !='\0'))
	{
		t_print(t->term->sound);
		return (1);
	}
	else if (buf != NULL && buf[0] == 4)
		gracefull_exit(g_p);
	return (0);
}

int	get_command(char **line, t_params *t)
{
	t->output += t_print(t->ps_one);
	t->ch_read = 0;
	while (t->ch_read >= 0)
	{
		t->ch_read = read(STDIN_FILENO, &t->buf, 99);
		if (t->ch_read < 0)
			break ;
		t->buf[t->ch_read] = '\0';
		if (check_exit(t->buf, t->res, t) || check_keys(t) == 1)
			continue ;
		else if (ft_strncmp(t->buf, "\n", t->ch_read + 1) != 0)
		{
			t->res = strcomb(t->res, t->buf);
			t->output += t_print(t->buf);
		}
		ioctl(STDIN_FILENO, FIONREAD, &t->check);
		if (t->check != 0)
			continue ;
		if (check_input(line, t) == 1)
			return (new_command(line, t));
	}
	return (1);
}
