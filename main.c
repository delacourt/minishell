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
	char quote[1024];
	char j;
	int sq;
	int dq;

	i = 0;
	j = 0;
	ft_memset(quote, 0, 1024);
	while (line[i] != '\0')
	{
		if (line[i] == '\\')
		{
			++i;
			if (line[i] == '\0')
				return (1);
		}
		else if (line[i] == '\"')
			quote[j++] = '\"';
		else if (line[i] == '\'')
			quote[j++] = '\'';
		++i;
	}
	j = ft_strlen(quote);
	if (j % 2 == 1)
		return (1);
	printf("%s\n", quote);
	i = 0;
	sq = 0;
	dq = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			++sq;
		}
		if (line[i] == '\"')
		{
			++dq;
		}



	}
	return (0); // a changer
}

int isbuiltin(char *line)
{
	char **tab;
	char *resu;
	int i;

	i = is_broken_quote(line);
	printf("%d\n", i);
	// tab = ft_split(line, ' ');
	// i = 0;
	// while(tab[i] != NULL)
	// {
	// 	printf("%s\n", tab[i]);
	// 	++i;
	// }
	// if (ft_strncmp("cd", tab[0], 2) == 0)
	// 	cd(line);
	// if (ft_strncmp("pwd", tab[0], 3) == 0)
	// 	pwd();
	// //free_le_tab
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
			exec_prog(line, NULL, envp);
        if (i == 0)
        	return (0);
		print_new_line();
    }
    return (0);
}
