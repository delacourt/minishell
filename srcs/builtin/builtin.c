/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:14:02 by velovo            #+#    #+#             */
/*   Updated: 2020/07/16 15:20:34 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

/*
**	echo pwd exit cd env
*/

int		echo2(char **tabl, int fd, int *lsc)
{
	int i;
	int is_n;

	i = 0;
	is_n = 0;
	if (tabl[0] != NULL && tabl[0][0] == '-' && is_empty_line(&tabl[0][1], 'n') == 0)
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

int		pwd(int fd, int *lsc)
{
	char *str;

	str = getcwd(NULL, 0);
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	free(str);
	*lsc = 0;
	return (1);
}

int		cd(char **tabl, int *lsc, char **envp)
{
	int i;
	char **c_pwd;
	char **o_pwd;
	char *gc_pwd;

	i = chdir(tabl[0]);
	*lsc = 0;
	if (i == -1)
	{
		*lsc = 1;
		write(2, "mash: cd: ", 10);
		write(2, tabl[0], ft_strlen(tabl[0]));
		write(2, ": No such file or directory\n", 28);
		return (1);
	}
	if ((c_pwd = get_env_variable(envp, "PWD")) != NULL && (o_pwd = get_env_variable(envp, "OLDPWD")) != NULL)
	{
		free(*o_pwd);
		*o_pwd = ft_strjoin("OLDPWD", &c_pwd[0][3]);
		free(*c_pwd);
		gc_pwd = getcwd(NULL, 0);
		*c_pwd = ft_strjoin("PWD=", gc_pwd);
		free(gc_pwd);
	}
	return (1);
}

void	print_env(char **envp, int fd, int *lsc)
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

int is_atoiable(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || ft_isdigit(str[i]) == 1)
		++i;
	while (str[i] != '\0' && ft_isdigit(str[i]) == 1)
		++i;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int		end(char **tabl, t_env *enviro)//3 cas de figure
{
	int i;

	if (enviro->ctrld == 0)
		write(2, "exit\n", 5);
	if (env_len(tabl) == 2 && ft_strlen(tabl[1]) > 0 && is_atoiable(tabl[1]) == 0)
		enviro->lsc = ft_atoi(tabl[1]);
	else if (ft_strlen(tabl[1]) > 0 && is_atoiable(tabl[1]) == 0)
	{
		write(2, "mash: exit: too many arguments\n", 31);
		if (enviro->lsc == 0)
			enviro->lsc = 1;
		return (0);
	}
	else if (env_len(tabl) > 1 && is_atoiable(tabl[1]) == 1)
	{
		write(2, "mash: exit: ", 12);
		write(2, tabl[1], ft_strlen(tabl[1]));
		write(2, ": numeric argument required\n", 28);
		enviro->lsc = 2;
	}
	if (enviro->lsc < 0)
		enviro->lsc = (enviro->lsc%256);
	return (3);
}
