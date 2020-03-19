#include "minishell.h"

int echo()
{
	return (1);
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