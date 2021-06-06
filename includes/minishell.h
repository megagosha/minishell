#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <curses.h>
# include <term.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <signal.h>
# include "../srcs/libft/libft.h"
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <string.h>

# define MEMERROR 10
# define TERM_INIT 11
# define FORK_ERROR 12
# define EMPTY 0
# define CMD 1
# define ARG 2
# define L_RDCT 3
# define R_RDCT 4
# define DR_RDCT 5
# define SEMIC 6
# define PIPE 7

typedef struct s_term
{
	char	*ku;
	char	*kd;
	char	*kr;
	char	*kl;
	char	*ks;
	char	*sound;
	char	*cr_zero;
	char	*ke;
	char	*cr_left;
	char	*delete_char;
	char	*clear;
	char	*up;
}	t_term;

typedef struct s_tok
{
	char			*str;
	int				type;
	struct s_tok	*prev;
	struct s_tok	*next;
}				t_tok;

typedef struct s_pipe
{
	int	fd[2][2];
	int	cur_pipe;
}	t_pipe;

typedef struct s_ncmd
{
	char	*cmd;
	char	*cmd_path;
	char	**argv;
	char	**envp;
}	t_ncmd;

typedef struct s_params {
	struct termios	*new_term;
	struct termios	*old_term;
	t_tok			*tok;
	t_term			*term;
	t_list			*hist;
	t_pipe			*pipe;
	t_ncmd			*cmd;
	char			**env;
	char			*ps_one;
	char			**exec_paths;
	int				output;
	char			buf[100];
	int				ch_read;
	int				check;
	char			*res;
	pid_t			pid;
	int				status;
	int				hist_pos;
	int				total_hist;
	int				i;
}	t_params;

extern t_params	*g_p;
char	*free_exec_path(char *str, char **exec);
int		prepare_command(t_ncmd *res, t_pipe *pi);
int		prep(t_pipe *pi);
t_tok	*skip_redirects(t_tok *tok);
void	init_cmd(t_ncmd *cmd, char **envp);
t_tok	*get_args(t_tok *tok, t_ncmd *cmd);
int		my_exec(t_params *params);
void	add_var(t_params *p, char *new_var, char *value);
void	ft_env(char **env);
int		my_export(char **input, t_params *p);
int		unset_var(char **var, t_params *p);
void	sigint(int sig);
void	init_terminal_data (t_params *p);
void	default_terminal(void);
void	change_term_config(void);
void	free_tok(t_tok *tok);
void	sigquit(int sig);
void	sigstop(int sig);
int		file_exist(char *filename);
int		exec_cmd(t_ncmd *res, t_pipe *pi);
t_tok	*skip_left(t_tok *tok);
int		if_pipe_right(t_tok *tok);
int		if_pipe_left(t_tok *tok);
void	switch_pipe(t_pipe *p);
void	check_builin(t_ncmd *res);
void	check_errno_in_child(t_ncmd *res);
int		count_args(t_tok *tok);
int		of(int i);
void	stopped_or_exit(t_ncmd *res, int status);
char	*get_pwd(void);
void	put_error(char *str);
void	print_error(char *str, int type);
void	exit_with_error(int error_code);
void	init_params(t_params *params, char **envp);
char	*get_var_by_name(char **haystack, const char *needle);
int		my_cd(char **args, t_params *params);
int		hist_change(int hist_pos, int max_hist, int dir);
int		new_command(char **line, t_params *t);
int		ft_key(int dir);
int		my_echo(char **input);
void	interrogate_terminal(t_term *term);
int		clear_line(t_term *term, const char *output);
int		delete_char(t_term *term, char *res, int output, char *ps_one);
int		ft_putc(int c);
int		t_print(char *str);
int		t_printerr(char *str);
char	*strcomb(char *str1, const char *str2);
void	update_ps_one(t_params *t);
void	update_var_by_name(t_params *p, char *new_var, char *value);
int		get_env(t_params *params, char **line, int *i);
void	get_quotes(t_params *params, char **line, int *i, char q);
int		my_exec(t_params *p);
void	check_env(t_params *params);
char	*rm_char(char *line, int i);
char	*strjoinf(char *str1, char *str2);
int		skipspace(t_params *params, char *line);
int		parse(t_params *params, char *line);
int		check_quotes(char *line);
void	skip_quotes(char *line, int *i, char q);
void	get_sep(t_params *params, char *line);
void	set_new_tok(t_params *params, char *str);
void	get_new_tok(t_params *params, char *line);
int		sort_rdct(t_params *params);
int		open_redirections(t_tok *tok);
int		is_redirect(int i);
int		check_sep(t_tok *tok);
char	*get_exec_path(t_params *p, t_ncmd *cmd, char **exec_paths);
int		get_command(char **line, t_params *t);
int		write_error(char *str);
t_tok	*new_tok(char *str);
void	set_type(t_tok *tok);
int		skipslash(t_params *params, char **line, int *i, int q);
void	gracefull_exit(t_params *p);
int		close_fd(t_tok *rdct);
int		get_status(t_params *params, char **line, int *i);
int		check_var(char *new_var);
#endif
