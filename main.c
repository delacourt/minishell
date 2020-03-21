/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:09:19 by delacourt         #+#    #+#             */
/*   Updated: 2020/03/13 17:26:18 by delacourt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_new_line()
{
	char c[] = "&> ";

	write(1, c, 3);
}

int exec_prog(char *line, char **argv, char **envp)
{
	pid_t pid;

    pid = fork();
    if (pid == 0)
        execve(line, argv, envp);
    else
        wait(&pid);
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

int isbuiltin(char *line)
{
	char **tab;
	int i;

	i = is_broken_quote(line);
	if (i != 0)
	{
		printf("broken pipe\n");
		return (i);
	}
	while (line[i] == ' ')
		++i;
	if (ft_strncmp(&line[i], "echo", 4) == 0 || ft_strncmp(&line[i], "cd", 2) == 0 || ft_strncmp(&line[i], "pwd", 3) == 0
		|| ft_strncmp(&line[i], "export", 6) == 0 || ft_strncmp(&line[i], "unset", 5) == 0 || ft_strncmp(&line[i], "env", 3) == 0
		|| ft_strncmp(&line[i], "exit", 2) == 0)
	{
		tab = ft_enhanced_split(line);
		if (ft_strncmp("echo", tab[0], 5) == 0)
			echo(&tab[1]);
		else if (ft_strncmp("pwd", tab[0], 3) == 0)
			pwd();
		free_arr(tab, i);
	}
	else
		printf("not a builtin\n");
	return (i);
}

int main(int argc, char **argv, char **envp)
{
	int i;
    char *line;
	char *path;

    print_new_line();
	while (1)
    {
        i = get_next_line(0, &line);

		if (isbuiltin(line) == 1)
			;
		else
			;//exec_prog(line, NULL, envp);
        if (i == 0)
        	return (0);
		print_new_line();
    }
    return (0);
}
