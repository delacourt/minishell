/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:09:19 by delacourt         #+#    #+#             */
/*   Updated: 2020/07/05 01:24:22 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/minishell.h"

void print_new_line(int lsc)
{
	char c[] = "&> ";
	char *str;
	int i;
	int j;

	if (lsc == 0)
	{
		ft_putstr_fd("\033[0;32m", 1);
		write(1, c, 3);
		ft_putstr_fd("\033[0m", 1);
	}
	else
	{
		ft_putstr_fd("\033[0;31m", 1);
		write(1, c, 3);
		ft_putstr_fd("\033[0m", 1);
	}
	str = getcwd(NULL, 0);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '/')
			++j;
		++i;
	}
	if (j > 1)
	{
		while (str[i] != '/' && i >= 0)
			--i;
		++i;
		ft_putstr_fd("\033[1;36m", 1);
		write(1, &str[i], ft_strlen(&str[i]));
		ft_putstr_fd("\033[0m", 1);
		write(1, ": ", 2);
	}
	else
	{
		ft_putstr_fd("\033[1;31m", 1);
		write(1, str, ft_strlen(str));
		ft_putstr_fd("\033[0m", 1);
		write(1, ": ", 2);
	}
	free(str);
}

int is_broken_quote(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			++i;
			while (line[i] != '\"' && line[i] != '\0')
			{
				if (line[i] == '\\')
					++i;
				++i;
			}
		}
		else if (line[i] == '\'')
		{
			++i;
			while (line[i] != '\'' && line[i] != '\0')
			{
				
				if (line[i] == '\\' && line[i + 1] != '\'')
					++i;
				++i;
			}
		}
		else if (line[i] == '\\')
			++i;
		if (line[i] == '\0')
			return (1);
		++i;
	}
	return (0); // a changer
}

int parse_exec(char *line, t_r_output redir, t_env *enviro, t_pipe *pip)
{
	char **tabl;
	int i;

	i = is_broken_quote(line);
	if (i != 0)
	{
		printf("broken pipe\n");
		return (i);
	}
	tabl = ft_enhanced_split(line, enviro);
	int j = 0;
	if (ft_strncmp(tabl[0], "echo", 5) == 0 || ft_strncmp(tabl[0], "cd", 3) == 0 || ft_strncmp(tabl[0], "pwd", 4) == 0
	|| ft_strncmp(tabl[0], "export", 7) == 0 || ft_strncmp(tabl[0], "unset", 6) == 0 || ft_strncmp(tabl[0], "env", 4) == 0
	|| ft_strncmp(tabl[0], "exit", 5) == 0 || ft_strncmp(tabl[0], "cd", 3) == 0)
	{
		if (pip->total > 1 && pip->nbr + 1 < pip->total && redir.out == 1)
			redir.out = pip->pipefd[pip->nbr][1];
		if (ft_strncmp("echo", tabl[0], 5) == 0)
			echo2(&tabl[1], redir.out, &enviro->lsc);
		else if (ft_strncmp("pwd", tabl[0], 4) == 0)
			pwd(redir.out, &enviro->lsc);
		else if (ft_strncmp("exit", tabl[0], 5) == 0)
			end(tabl, enviro);
		else if (ft_strncmp("cd", tabl[0], 3) == 0)
			cd(&tabl[1], &enviro->lsc);
		else if (ft_strncmp("env", tabl[0], 4) == 0)
			print_env(enviro->envp, redir.out, &enviro->lsc);
		else if (ft_strncmp("export", tabl[0], 7) == 0)
			enviro->envp = export_new(&tabl[1], enviro);
		else if (ft_strncmp("unset", tabl[0], 6) == 0)
			enviro->envp = unset_new(&tabl[1], enviro);
		if (pip->total > 1 && pip->nbr + 1 < pip->total)
			close(pip->pipefd[pip->nbr++][1]);
	}
	else if (tabl[0] != NULL)
	{
		search_and_exec(tabl, enviro->envp, &enviro->lsc, redir, pip);
	}
	free_env(tabl);
	return (i);
}

int ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int i;
	int error;
	int n_pipe;
    char *line;
	char **tabl;
	char **p_tab;
	//char **tenv;
	t_env enviro;
	t_pipe pip;
	(void)argc;
	(void)argv;
	enviro.lsc = 0;
	struct termios s_set;
	struct termios backup;
	t_r_output redir;

	// tcgetattr(0, &s_set);
	// s_set.c_lflag &= ~(ICANON | ECHO | ISIG);
	// tcsetattr(0, 0, &s_set);

	enviro.envp = new_env(envp); //free lenv a la fin wsh
	signal(SIGINT, sighandler); //mdr cest pour pas quitter le prog sans fermer le terminal
    print_new_line(enviro.lsc);

	tcgetattr(0, &backup);
	tcgetattr(0, &s_set);
	s_set.c_lflag &= ~(ICANON | ECHO | ISIG);
	for (int j = 0; j < NCMD; ++j)
		enviro.histo[j] = NULL;
	enviro.h_len = 0;
	error = 0;
	while (1)
    {
		tcsetattr(0, 0, &s_set);   
		i = inter_line(&line, &enviro); //le exit(0) dedans ducoup cest full leaks (fin la aussi mdr) mais soef pour le moment ptet free line aussi mdr
		tcsetattr(0, 0, &backup);

		write(1, "\n", 1);
		tabl = split_semi_colon(line);
		i = 0;

		//printf("              %s\n", line);
		while (tabl[i] != NULL)
		{
			//printf("%s\n", tabl[i]);
			if ((error = split_pipe(tabl[i], &p_tab)) == 1)	//free chaque p_tab
			{
				enviro.lsc = 1;
				write(1, "mash: syntax error, unexpected token\n", 37);
				error = 1;
			}
			fill_t_pipe(&pip, p_tab); //close les FD gerer les malloc qui marchent pas
			n_pipe = 0;
			while (error == 0 && p_tab[n_pipe] != NULL)
			{
				//  for (int z = 0; p_tab[z] != NULL; ++z)
				//printf("p_tab: %s\n", p_tab[n_pipe]);
				if (split_r_in_out(p_tab[n_pipe], &redir, &enviro) > 0) //surement a free la dedans aussi
				{
					enviro.lsc = 1;
					write(1, "mash: syntax error, unexpected token\n", 37);
					error = 1;
				}
				//printf("hey c'est le main\n");
				if (error == 0 && parse_exec(redir.ret, redir, &enviro, &pip) == 1) //else if ici
				{
					;
				}
				close_redirect(&redir);
				++n_pipe;
			}
			free_env(p_tab);
			++i;
			error = 0;
		}
		free_env(tabl);
		//print_env(tabl, 1, &enviro.lsc);
		//free_env(tabl);
		print_new_line(enviro.lsc);
	}
    return (0);
}
