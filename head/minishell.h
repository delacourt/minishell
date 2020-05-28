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
#include "get_next_line.h"
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


int cd(char **tabl);
int pwd();
int echo2(char **tabl);
void end(char **tabl, t_env *enviro);
void	*free_arr(char **tabl, int j);
char	**ft_enhanced_split(char const *str, char **envp);
void sighandler(int signum);
void print_new_line();
int exec_prog(char *line, char **argv, char **envp);
int search_and_exec(char **tabl, char **envp, int *lsc);
char **split_semi_colon(char *line);
char **new_env(char **envp);
int env_len(char **env);
void print_env(char **envp);
void free_env(char **envp);
int search_the_equal(char *str);
int	count_words(const char *str);
int search_the_equal(char *str);

char *test1212(int *dep, int *i, char *word, const char *str, char **envp);

char **export_new(char **arg, t_env *enviro);
char **unset_new(char **arg, t_env *enviro);

int inter_line(char **line, t_env *enviro);

#endif
