#include "../head/minishell.h"

int echo2(char **tabl)
{
	int i;
	int is_n;

	i = 0;
	is_n = 0;
	if (ft_strncmp(tabl[0], "-n", 2) == 0)
	{
		is_n = 1;
		i = 1;
	}
	while (tabl[i] != NULL)
	{
		write(1, tabl[i], ft_strlen(tabl[i]));
		++i;
		if (tabl[i] != NULL)
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

void end(char **tabl, t_env *enviro)
{
	int i;

	free_env(enviro->envp);
	free_env(tabl);
	if (enviro->lsc == 0)
		exit(0);
	exit(1);
}

int cd(char **tabl)
{
	int i;
	
	i = chdir(tabl[0]);
	if (i == -1)
	{
		write(1, "mash: cd: ", 10);
		write(1, tabl[0], ft_strlen(tabl[0]));
		write(1, ": No such file or directory\n", 28);
	}
	return (1);
}

void print_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		write(1, envp[i], ft_strlen(envp[i]));
		write(1, "\n", 1);
		++i;
	}
}
