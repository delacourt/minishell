/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 13:25:30 by avan-pra          #+#    #+#             */
/*   Updated: 2020/07/20 13:25:31 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

int		is_builtin(char *str)
{
	if (ft_strncmp(str, "echo", 5) == 0
		|| ft_strncmp(str, "cd", 3) == 0
		|| ft_strncmp(str, "pwd", 4) == 0
		|| ft_strncmp(str, "export", 7) == 0
		|| ft_strncmp(str, "unset", 6) == 0
		|| ft_strncmp(str, "env", 4) == 0
		|| ft_strncmp(str, "exit", 5) == 0
		|| ft_strncmp(str, "cd", 3) == 0)
		return (0);
	return (1);
}

int		hub_broken_quote(char *line, t_env *enviro)
{
	int ret;

	ret = is_broken_quote(line);
	if (ret != 0)
	{
		write(2, "mash: syntax error, unexpected token\n", 37);
		enviro->lsc = 1;
		return (ret);
	}
	return (0);
}

int		builtin_caller
	(t_pipe *pip, char **tabl, t_env *enviro, t_r_output redir)
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
	--pip->founded;
	return (0);
}

int		parse_exec(char *line, t_r_output redir, t_env *enviro, t_pipe *pip)
{
	char	**tabl;
	int		ret;

	if ((ret = hub_broken_quote(line, enviro)) != 0)
		return (ret);
	tabl = ft_enhanced_split(line, enviro);
	if (is_builtin(tabl[0]) == 0)
	{
		if ((ret = builtin_caller(pip, tabl, enviro, redir)) != 0)
			return (ret);
	}
	else if (tabl[0] != NULL && ft_strlen(tabl[0]) != 0)
		ret = search_and_exec(tabl, enviro, redir, pip);
	free_env(tabl);
	free(tabl);
	return (ret);
}
