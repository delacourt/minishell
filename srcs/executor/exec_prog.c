/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prog.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:30:43 by avan-pra          #+#    #+#             */
/*   Updated: 2020/07/17 15:27:02 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

int			exec_prog(t_exec *ex, t_r_output redir, t_pipe *pip, int i)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		if (pip->total > 1 && pip->nbr != 0)
			dup2(pip->pipefd[pip->nbr - 1][0], 0);
		if (pip->total > 1 && pip->nbr + 1 < pip->total)
			dup2(pip->pipefd[pip->nbr][1], 1);
		if (redir.out != 1)
			dup2(redir.out, 1);
		if (redir.in != 0)
			dup2(redir.in, 0);
		i = pip->total - 2;
		while (i >= 0)
		{
			close(pip->pipefd[i][0]);
			close(pip->pipefd[i][1]);
			--i;
		}
		execve(ex->path, ex->argv, ex->envp);
	}
	pip->pid[pip->nbr] = pid;
	++pip->nbr;
	return (pid);
}

int			absolute_path
	(t_exec *ex, t_env *enviro, t_pipe *pip, t_r_output redir)
{
	struct stat	statbuff;

	ex->path = ex->argv[0];
	if (stat(ex->argv[0], &statbuff) == 0)
	{
		if (S_ISDIR(statbuff.st_mode) == 0)
			enviro->lsc = exec_prog(ex, redir, pip, 0);
	}
	else
	{
		enviro->lsc = 1;
		--pip->founded;
		write(2, "mash: no such file or directory: ", 33);
		write(2, ex->argv[0], ft_strlen(ex->argv[0]));
		write(2, "\n", 1);
		return (1);
	}
	return (0);
}

/*
**	ca leak ici avec pathed (peut etre)
*/

int			relative_path
	(t_exec *ex, t_env *enviro, t_r_output redir, t_pipe *pip)
{
	struct stat	statbuff;

	ex->path = ft_str_slash_join(ex->argv, ex->c_path);
	if (stat(ex->path, &statbuff) == 0)
	{
		enviro->lsc = exec_prog(ex, redir, pip, 0);
		free(ex->path);
		free(ex->c_path);
		return (0);
	}
	return (1);
}

int			relative_notfound(t_env *enviro, t_pipe *pip, t_exec *ex)
{
	enviro->lsc = 1;
	--pip->founded;
	write(2, "mash: command not found: ", 25);
	write(2, ex->argv[0], ft_strlen(ex->argv[0]));
	write(2, "\n", 1);
	return (1);
}

int			search_and_exec
	(char **tabl, t_env *enviro, t_r_output redir, t_pipe *pip)
{
	struct stat	statbuff;
	t_exec		ex;
	char		**pathed;
	int			i;
	int			ret;

	i = setup_search(&ex, enviro, tabl);
	if (ft_strchr(tabl[0], '/'))
		return (absolute_path(&ex, enviro, pip, redir));
	else
	{
		pathed = ft_split(ex.path, ':');
		i = 0;
		while (pathed[i] != NULL)
		{
			ex.c_path = pathed[i];
			ret = relative_path(&ex, enviro, redir, pip);
			if (ret == 0)
				return (ret);
			++i;
		}
	}
	relative_notfound(enviro, pip, &ex);
	return (1);
}
