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
	int ret = 0;

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
		{
			free_env(tabl);
			free(tabl);
			return (3);
		}
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
		ret = search_and_exec(tabl, enviro->envp, &enviro->lsc, redir, pip);
	}
	free_env(tabl);
	free(tabl);
	return (ret);
}

int ft_putchar(int c)
{
	write(1, &c, 1);
	return (0);
}

int main(int argc, char **argv, char **envp)
{
	int i;
	int g;
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
		i = inter_line(&line, &enviro); //le exit(0) dedans ducoup cest full leaks (fin la aussi mdr) mais soef pour le moment ptet free line aussi mdr non pas free line utilie pour l'histo
		tcsetattr(0, 0, &backup);

		write(1, "\n", 1);
		tabl = split_semi_colon(line);
		i = 0;

		while (tabl[i] != NULL)
		{
			error = split_pipe(tabl[i], &p_tab);
			if (error == 1)	//free chaque p_tab
			{
				enviro.lsc = 1;
				write(1, "mash: syntax error, unexpected token\n", 37);
				error = 1;
			}
			fill_t_pipe(&pip, p_tab); //close les FD gerer les malloc qui marchent pas
			pip.pid = calloc(pip.total, sizeof(int));
			n_pipe = 0;
			while (error == 0 && p_tab[n_pipe] != NULL)
			{
				error = split_r_in_out(p_tab[n_pipe], &redir, &enviro);
				if (error > 0) //surement a free la dedans aussi
				{
					enviro.lsc = 1;
					if (error == 1)
						write(1, "mash: syntax error, unexpected token\n", 37);
					error = 1;
				}
				if (error == 0) //else if ici
				{
					error = parse_exec(redir.ret, redir, &enviro, &pip);
					if (error == 3) /* 3 c'est pour le exit */
					{
						close_redirect(&redir);
						for (g = 0; pip.pipefd[g] != NULL; ++g)
						{
							//close(pip.pipefd[g][0]);
							//close(pip.pipefd[g][1]);
							free(pip.pipefd[g]);
						}
						if (g > 0)
							close(pip.pipefd[g][1]);
						free(pip.pipefd);
						free_env(p_tab);
						free(p_tab);
						free_env(tabl);
						free(tabl);
						free_env(enviro.envp);
						free(enviro.envp);
						free_env(&enviro.histo[1]);
						free(pip.pid);
						return (enviro.lsc);
					}
					else if (error == 1) //prog pas trouvé
					{
						//printf("yo\n");
						pip.pid[pip.nbr++] = -1;
						error = 0;	
					}
				}
				close_redirect(&redir);
				++n_pipe;
			}
			for (int p = pip.total - 2; p >= 0; --p)
			{
				close(pip.pipefd[p][0]);
				close(pip.pipefd[p][1]);
			}
			//printf("yoooo\n");
			for (int v = 0; v < pip.total; ++v)
			{
				waitpid(pip.pid[v], &enviro.lsc, 0);					//waitpid ici
			}
			for (int g = 0; pip.pipefd[g] != NULL; ++g)
				free(pip.pipefd[g]);
			free(pip.pipefd);
			free_env(p_tab);
			free(p_tab);
			free(pip.pid);
			++i;
		// 	error = 0;
		}
		free_env(tabl);
		free(tabl);

		print_new_line(enviro.lsc);
	}
    return (0);
}
