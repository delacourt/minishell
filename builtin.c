#include "minishell.h"

int echo(char **tab)
{
	int i;
	int is_n;

	i = 0;
	is_n = 0;
	if (ft_strncmp(tab[0], "-n", 2) == 0)
	{
		is_n = 1;
		i = 1;
	}
	while (tab[i] != NULL)
	{
		write(1, tab[i], ft_strlen(tab[i]));
		++i;
		if (tab[i] != NULL)
			write(1, " ", 1);
	}
	if (is_n == 0)
	write(1, "\n", 1);
	return (0);
}

int pwd()
{
	char *str;

	str = getcwd(NULL, 0);
	ft_putstr_fd(str, 1);
	ft_putchar_fd('\n', 1);
	free(str);
	return (1);
}

void end(char **tab)
{
	int i;

	i = 0;
	while(tab[i] != NULL)
		++i;
	free_arr(tab, i);
	exit(0);
}

int cd(char *line)
{
	return (1);
}