#include "minishell.h"

void	interrogate_terminal(t_term *term)
{
	term->ku = tgetstr("ku", NULL);
	term->kd = tgetstr("kd", NULL);
	term->cr_left = tgetstr("le", NULL);
	term->kr = tgetstr("kr", NULL);
	term->kl = tgetstr("kl", NULL);
	term->ks = tgetstr("ks", NULL);
	term->ke = tgetstr("ke", NULL);
	term->clear = tgetstr("cd", NULL);
	term->cr_zero = tgetstr("cr", NULL);
	term->delete_char = tgetstr("dc", NULL);
	term->up = tgetstr("up", NULL);
	change_term_config();
}

void	init_terminal_data (t_params *p)
{
	int		success;
	char	*termtype;

	termtype = getenv ("TERM");
	if (termtype == 0)
		exit_with_error(TERM_INIT);
	success = tgetent (NULL, termtype);
	if (success < 0)
		exit_with_error(TERM_INIT);
	if (success == 0)
		exit_with_error(TERM_INIT);
	tcgetattr(0, p->new_term);
	ft_memcpy(g_p->old_term, g_p->new_term, sizeof(struct termios));
	p->new_term->c_lflag &= ~(ICANON);
	p->new_term->c_lflag &= ~(ECHO);
	p->new_term->c_cc[VTIME] = 0;
	p->new_term->c_cc[VMIN] = 1;
}

void	default_terminal(void)
{
	tcsetattr(0, TCSANOW, g_p->old_term);
	tputs(g_p->term->ke, STDIN_FILENO, ft_putc);
}

void	change_term_config(void)
{
	tcsetattr(0, TCSANOW, g_p->new_term);
	tputs(g_p->term->ks, STDIN_FILENO, ft_putc);
}

void	gracefull_exit(t_params *p)
{
	default_terminal();
	exit(EXIT_SUCCESS);
}
