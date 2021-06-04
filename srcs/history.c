#include "../includes/minishell.h"

int	hist_change(int hist_pos, int max_hist, int dir)
{
	if (dir != -1 && dir != 1)
		return (hist_pos);
	hist_pos += dir;
	if (hist_pos < -1)
		return (-1);
	if (hist_pos >= max_hist)
		return (0);
	return (hist_pos);
}

int	new_command(char **line, t_params *t)
{
	if (t->res == NULL)
	{
		*line = NULL;
		printf("\n");
		return (1);
	}
	t->output += t_print(t->buf);
	t->total_hist++;
	if (t->hist == NULL && t->res != NULL)
	{
		t->hist = ft_lstnew(ft_strdup(t->res));
	}
	else if (t->res != NULL)
	{
		ft_lstadd_front(&t->hist, ft_lstnew(ft_strdup(t->res)));
		t->hist_pos = -1;
	}
	t->output = 0;
	*line = t->res;
	t->res = NULL;
	return (1);
}

int	ft_key(int dir)
{
	int	prev_pos;

	prev_pos = g_p->hist_pos;
	g_p->hist_pos = hist_change(g_p->hist_pos, g_p->total_hist, dir);
	if (prev_pos == g_p->hist_pos)
		return (1);
	g_p->output = clear_line(g_p->term, ft_lstgetnum(g_p->hist, prev_pos));
	g_p->res = ft_strdup(ft_lstgetnum(g_p->hist, g_p->hist_pos));
	g_p->output += t_print(g_p->ps_one);
	g_p->output += t_print(g_p->res);
	return (1);
}
