#include "../head/minishell.h"

int echo2(char **tabl, int fd, int *lsc)
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
		write(fd, tabl[i], ft_strlen(tabl[i]));
		++i;
		if (tabl[i] != NULL)
			write(fd, " ", 1);
	}
	*lsc = 0;
	if (is_n == 0)
		write(fd, "\n", 1);
	return (0);
}

int pwd(int fd, int *lsc)
{
	char *str;

	str = getcwd(NULL, 0);
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	free(str);
	*lsc = 0;
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

int cd(char **tabl, int *lsc)
{
	int i;
	
	i = chdir(tabl[0]);
	*lsc = 0;
	if (i == -1)
	{
		*lsc = 1;
		write(1, "mash: cd: ", 10);
		write(1, tabl[0], ft_strlen(tabl[0]));
		write(1, ": No such file or directory\n", 28);
	}
	return (1);
}

void print_env(char **envp, int fd, int *lsc)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		write(fd, envp[i], ft_strlen(envp[i]));
		write(fd, "\n", 1);
		++i;
	}
	*lsc = 0;
}
