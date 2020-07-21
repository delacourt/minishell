/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 16:21:56 by avan-pra          #+#    #+#             */
/*   Updated: 2020/07/21 16:22:14 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 32
# define NCMD 11
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <curses.h>
# include <term.h>
# include <termcap.h>
# include <termios.h>

typedef struct	s_pipe
{
	int **pipefd;
	int nbr;
	int total;
	int	founded;
	int *pid;
}				t_pipe;

typedef struct	s_env
{
	char	**envp;
	int		lsc;
	char	*histo[NCMD];
	int		h_len;
}				t_env;

typedef struct	s_key
{
	char	g[4];
	char	d[4];
	char	h[4];
	char	b[4];
}				t_key;

typedef struct	s_r_output
{
	int		out;
	int		in;
	char	*ret;
}				t_r_output;

typedef struct	s_etup_i_o
{
	int		*i;
	int		*quotes;
	int		ret;
}				t_etup_i_o;

typedef struct	s_read
{
	char	t;
	char	*tst;
	char	*tmp;
	char	*hold;
	int		ou;
	char	*c_key;
	int		multi;
	int		old_multi;
	int		multi_pipe;
}				t_read;

typedef struct	s_inter_read
{
	struct termios	s_set;
	struct termios	backup;
}				t_inter_read;

typedef struct	s_word
{
	int		*i;
	int		*dep;
	int		*c_split;
	char	*word;
}				t_word;

typedef struct	s_doll
{
	char	*tmp;
	char	*ret;
	char	*tmp2;
	char	**envp;
	int		penv;
	int		len;
	int		lentest;
	int		solo;
}				t_doll;

typedef struct	s_exec
{
	char	*path;
	char	**argv;
	char	**envp;
	char	*c_path;
}				t_exec;

typedef struct	s_main
{
	int		i;
	int		g;
	int		error;
	int		n_pipe;
	char	*line;
	char	**tabl;
	char	**p_tab;
}				t_main;

/*
**	better_split
*/

int				advance(const char *str);
void			skip_space(const char *str, int *i);
int				count_split(const char *str);
int				count_words(const char *str);
char			*fill_with_enviro(const char *str, t_env enviro, t_word *giv);
char			*ft_itoa(int n);
int				find_the_end_env(const char *str);
int				is_only_doll(char *word, const char *str, int i);
void			*free_arr(char **tabl, int j);
void			*word_setup(const char *str, t_word *giv);
char			**ft_enhanced_split(char const *str, t_env *enviro);
char			*fill_word(const char *str, t_env *enviro, int *c_split);

/*
**	builtin
*/

int				echo2(char **tabl, int fd, int *lsc);
int				pwd(int fd, int *lsc);
int				cd(char **tabl, int *lsc);
void			print_env(char **envp, int fd, int *lsc);

/*
**	environement
*/

char			**unset_new(char **arg, t_env *enviro);
int				search_the_equal(char *str);
void			free_env(char **envp);
int				env_len(char **env);
char			**new_env(char **envp);
char			**export_new(char **arg, t_env *enviro);

/*
**	executor
*/

int				search_and_exec
				(char **tabl, t_env *enviro, t_r_output redir, t_pipe *pip);
char			*ft_str_slash_join(char **tabl, char *pathed);
int				setup_search(t_exec *ex, t_env *enviro, char **tabl);
int				parse_exec
				(char *line, t_r_output redir, t_env *enviro, t_pipe *pip);

/*
**	main
*/

int				perfect_exit
				(t_r_output *redir, t_pipe *pip, t_env *enviro, t_main *hub);
void			close_and_wait(t_pipe *pip, t_env *enviro, t_main *hub);
void			setup_new_input(t_main *hub, t_env *enviro);
void			get_line_split_semi_colon
				(t_inter_read *term, t_main *hub, t_env *enviro);
void			setup_pipe_split(t_main *hub, t_env *enviro, t_pipe *pip);
int				get_the_line(t_inter_read *term, char **line, t_env *enviro);
void			split_pipe_error
				(int *error, t_env *enviro, t_pipe *pip, char **p_tab);
void			split_r_in_out_error(int *error, t_env *enviro, t_pipe *pip);
int				is_empty_line(char *str);
void			print_new_line(int lsc);
void			sighandler(int signum);

/*
**	reader
*/

int				inter_line(char **line, t_env *enviro);
void			setup_intera_mode(t_inter_read *term);
void			fill_key(t_key *key);
void			put_in_histo(t_env *enviro, char *tst);
void			put_char_in_str(char *tst, int len, char c);

void			k_left(t_key key, int *end, t_read *t_r);
void			k_right(t_key key, int *end, t_read *t_r);
void			k_up(t_env *enviro, t_read *t_r, t_key key, int *end);
void			k_down(t_env *enviro, t_read *t_r, t_key key, int *end);

int				k_enter(t_env *enviro, char **line, t_read *t_r);
void			k_ctrl_c(t_env *enviro, t_read *t_r, int *end);
void			k_normal(t_read *t_r, int *end);
void			k_del(t_read *t_r, int *end, t_key key);
void			write_char(t_read *t_r, int *end, t_key key);

/*
**	spliter
*/

int				is_broken_pipe(char *str);
int				is_broken_quote(char *line);
int				split_pipe(char *line, char ***attach);
int				fill_t_pipe(t_pipe *pip, char **p_tab);
int				count_pipe(char *line);
int				len_line(char *line);
void			copy_word(char *src, char *dest);
int				split_r_in_out(char *line, t_r_output *redir, t_env *enviro);
int				fd_checker
				(char *line, t_etup_i_o *giv, t_r_output *redir, t_env *enviro);
int				ft_strlen_redirect(char *line, char red);
void			close_redirect(t_r_output *redir);
char			*get_file_name(char *str, t_env *enviro);
int				check_redir_error(char *line, char c);
char			**split_semi_colon(char *line);

#endif
