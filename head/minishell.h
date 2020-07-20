/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:14:41 by delacourt         #+#    #+#             */
/*   Updated: 2020/03/13 15:27:48 by delacourt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 32
# define NCMD 11
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <curses.h>
#include <term.h>
#include <termcap.h>
#include <termios.h>

typedef struct s_pipe
{
	int **pipefd;
	int nbr;
	int total;
	int	founded;
	int *pid;
}				t_pipe;

typedef struct	s_env
{
	char **envp;
	int lsc;
	char *histo[NCMD];
	int h_len;
}				t_env;

typedef struct	s_key
{
	char g[4];
	char d[4];
	char h[4];
	char b[4];
}				t_key;

typedef struct  s_r_output
{
    int out;
    int in;
	char *ret;
}           t_r_output;

typedef struct  s_etup_i_o
{
	int		*i;
	int		*quotes;
	int		ret;
}           t_etup_i_o;

typedef struct  s_read
{
	char	t;
	char	*tst;
	char	*tmp;
	char	*hold;
	int		ou;
	char	*c_key;
}           t_read;

typedef struct	s_inter_read
{
	struct termios s_set;
	struct termios backup;
}				t_inter_read;

typedef struct	s_word
{
	int		*i;
	int		*dep;
	int		*c_split;
	char	*word;
}          		t_word;

typedef struct	s_doll
{
	char	*tmp;
	char	*ret;
	char	*tmp2;
	int		penv;
	int		len;
	int		lentest;
	char	**envp;
	int		solo;
}				t_doll;

typedef struct	s_exec
{
	char	*path;
	char	**argv;
	char	**envp;
	char	*c_path;
}          		t_exec;

typedef struct	s_main
{
	int		i;
	int		g;
	int		error;
	int		n_pipe;
    char	*line;
	char	**tabl;
	char	**p_tab;
}          		t_main;

int cd(char **tabl, int *lsc);
int pwd(int fd, int *lsc);
int echo2(char **tabl, int fd, int *lsc);
int end(char **tabl, t_env *enviro);
void	*free_arr(char **tabl, int j);
char	**ft_enhanced_split(char const *str, t_env *enviro);
void sighandler(int signum);
void print_new_line(int lsc);
int exec_prog(t_exec *ex, t_r_output redir, t_pipe *pip, int i);
char **split_semi_colon(char *line);
char **new_env(char **envp);
int env_len(char **env);
void print_env(char **envp, int fd, int *lsc);
void free_env(char **envp);
int search_the_equal(char *str);

char *fill_with_enviro(const char *str, t_env enviro, t_word *giv);

char **export_new(char **arg, t_env *enviro);
char **unset_new(char **arg, t_env *enviro);

int		fd_checker(char *line, t_etup_i_o *pass, t_r_output *redir, t_env *enviro);

int		split_r_in_out(char *line, t_r_output *redir, t_env *enviro);
void    close_redirect(t_r_output *redir);
int     ft_strlen_redirect(char *line, char red);
char    *get_file_name(char *str, t_env *enviro);
int 	check_redir_error(char *line, char c);

int split_pipe(char *line, char ***attach);

int fill_t_pipe(t_pipe *pip, char **p_tab);

int is_broken_quote(char *line);

void	setup_intera_mode(t_inter_read *term);
void	put_in_histo(t_env *enviro, char *tst);
void	fill_key(t_key *key);
void	put_char_in_str(char *tst, int len, char c);

void	k_left(t_key key, int *end, t_read *t_r);
void	k_right(t_key key, int *end, t_read *t_r);
void	k_up(t_env *enviro, t_read *t_r, t_key key, int *end);
void	k_down(t_env *enviro, t_read *t_r, t_key key, int *end);
void	k_down_next(t_env *enviro, t_read *t_r, t_key key, int *end);

int		k_enter(t_env *enviro, char **line, t_read *t_r);
void	k_ctrl_c(t_env *enviro, t_read *t_r, int *end);
void	k_normal(t_read *t_r, int *end);
void	k_del(t_read *t_r, int *end, t_key key);
void	write_char(t_read *t_r, int *end, t_key key);

void	check_key(t_env *enviro, t_read *t_r, int *end, t_key key);
void	setup_read(t_key *key, t_read *t_r, char c_key[4], int *end);
int		inter_line(char **line, t_env *enviro);

int		count_split(const char *str);
int		count_words(const char *str);
char	*fill_word(const char *str, t_env *enviro, int *j); //mettre le j en struct et tt
int		advance(const char *str);

void	skip_space(const char *str, int *i);
void	*word_setup(const char *str, t_word *giv);

char			*ft_itoa(int n);
int				find_the_end_env(const char *str);
int				is_only_doll(char *word, const char *str, int i);

void	copy_word(char *src, char *dest);
int		len_line(char *line);
int		count_pipe(char *line);
int		fill_t_pipe(t_pipe *pip, char **p_tab);

int		search_and_exec(char **tabl, t_env *enviro, t_r_output redir, t_pipe *pip);
int		setup_search(t_exec *ex, t_env *enviro, char **tabl);
char	*ft_str_slash_join(char **tabl, char *pathed);

int		parse_exec(char *line, t_r_output redir, t_env *enviro, t_pipe *pip);
int		builtin_caller(t_pipe *pip, char **tabl, t_env *enviro, t_r_output redir);
int		hub_broken_quote(char *line, t_env *enviro);
int		is_builtin(char *str);

int		perfect_exit(t_r_output *redir, t_pipe *pip, t_env *enviro, t_main *hub);
void	close_and_wait(t_pipe *pip, t_env *enviro, t_main *hub);
void	setup_new_input(t_main *hub, t_env *enviro);
void	get_line_split_semi_colon(t_inter_read *term, t_main *hub, t_env *enviro);
void	setup_pipe_split(t_main *hub, t_env *enviro, t_pipe *pip);

int		get_the_line(t_inter_read *term, char **line, t_env *enviro);
void	split_pipe_error(int *error, t_env *enviro, t_pipe *pip, char **p_tab);
void	split_r_in_out_error(int *error, t_env *enviro, t_pipe *pip);

#endif
