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


int cd(char **tabl, int *lsc);
int pwd(int fd, int *lsc);
int echo2(char **tabl, int fd, int *lsc);
int end(char **tabl, t_env *enviro);
void	*free_arr(char **tabl, int j);
char	**ft_enhanced_split(char const *str, t_env *enviro);
void sighandler(int signum);
void print_new_line(int lsc);
int exec_prog(char *line, char **argv, char **envp, t_r_output redir, t_pipe *pip);
int search_and_exec(char **tabl, char **envp, int *lsc, t_r_output redir, t_pipe *pip);
char **split_semi_colon(char *line);
char **new_env(char **envp);
int env_len(char **env);
void print_env(char **envp, int fd, int *lsc);
void free_env(char **envp);
int search_the_equal(char *str);
int	count_words(const char *str);

char	*fill_word(const char *str, t_env *enviro, int *j); //mettre le j en struct et tt
int		advance(const char *str);

char *test1212(int *dep, int *i, char *word, const char *str, t_env enviro, int *j);

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

int inter_line(char **line, t_env *enviro);
void put_in_histo(t_env *enviro, char *tst);
void fill(t_key *key);
void test1213(char *tst, int len, char c);

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

#endif
