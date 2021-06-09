#include "minishell.h"

int	write_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

void	go_up_new_lines(int new_lines)
{
	if (new_lines > 1)
	{
		while (new_lines >= 0)
		{
			t_print(g_p->term->up);
			new_lines--;
		}
	}
	return ;
}

int	clear_line(t_term *term, const char *line)
{
	struct winsize	w;
	int				c;
	int				new_lines;
	int				cil;

	c = 0;
	cil = 0;
	new_lines = 0;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	while (line[c] != '\0')
	{
		if (line[c] == '\n' || cil >= w.ws_col)
		{
			cil = 0;
			new_lines++;
		}
		cil++;
		c++;
	}
	go_up_new_lines(new_lines);
	t_print(term->cr_zero);
	t_print(term->clear);
	return (0);
}

int	delete_char(t_term *term, char *res, int output, char *ps_one)
{
	if (ft_strlen(res) == 0)
		return (0);
	output -= ft_strlen(ps_one);
	if (output <= 0)
		return (0);
	res[output - 1] = '\0';
	t_print(term->cr_left);
	t_print(term->delete_char);
	return (-1);
}
