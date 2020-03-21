#include "minishell.h"

int echo(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		write(1, tab[i], ft_strlen(tab[i]));
		write(1, " ", 1);
		++i;
	}
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

int cd(char *line)
{
	int i = 0;

	while(line[i] == ' ')
		++i;
	i = i + 2;
	printf("yo\n");
	return (1);
}