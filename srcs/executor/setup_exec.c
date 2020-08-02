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

static int		is_builtin(char *str)
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

static int		hub_broken_quote(char *line, t_env *enviro)
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

static int		builtin_caller
	(t_pipe *pip, char **tabl, t_env *enviro, t_r_output redir)
{
	--pip->founded;
	if (pip->total > 1 && pip->nbr + 1 < pip->total && redir.out == 1)
		redir.out = pip->pipefd[pip->nbr][1];
	if (ft_strncmp("echo", tabl[0], 5) == 0)
		echo2(&tabl[1], redir.out, &enviro->lsc);
	else if (ft_strncmp("pwd", tabl[0], 4) == 0)
		pwd(redir.out, &enviro->lsc);
	else if (ft_strncmp("exit", tabl[0], 5) == 0)
		return (end(tabl, enviro));
	else if (ft_strncmp("cd", tabl[0], 3) == 0)
		cd(&tabl[1], &enviro->lsc, enviro->envp);
	else if (ft_strncmp("env", tabl[0], 4) == 0)
		print_env(enviro->envp, redir.out, &enviro->lsc);
	else if (ft_strncmp("export", tabl[0], 7) == 0)
		enviro->envp = export_new(&tabl[1], enviro);
	else if (ft_strncmp("unset", tabl[0], 6) == 0)
		enviro->envp = unset_new(&tabl[1], enviro);
	if (pip->total > 1 && pip->nbr + 1 < pip->total)
		close(pip->pipefd[pip->nbr++][1]);
	return (0);
}

char *test1212(char *str, int pos, char *line)
{
	char	*tmp;
	int		i;

	i = pos;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			tmp = str;
			str = ft_calloc(ft_strlen(str) + ft_strlen(line) + 2, sizeof(char));
			ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
			free(tmp);
			tmp = ft_strdup(&str[i]);
			str[i] = '\\';
			ft_strlcpy(&str[i + 1], tmp, ft_strlen(tmp) + 1);
			free(tmp);
			++i;
		}
		++i;
	}
	return (str);
}

static void			set_len(t_doll *dol, char *envp, char *line)
{
	dol->len = search_the_equal(envp);
	dol->lentest = find_the_end_env(line);
	if (dol->len < dol->lentest)
		dol->len = dol->lentest;
}

static char			*re_back(int o, char *str, int *i, char *line)
{
	while (o < ft_strlen(str))
	{
		if (str[*i] == '\\')
			++i;
		else if (str[*i] == '\'')
			str = test1212(str, o++, line);
		else if (str[*i] == '\"')
			str = test1212(str, o++, line);
		++o;
	}
	return (str);
}

static		char *prel_ending(char *str)
{
	char *tmp;
	
	tmp = str;
	str = calloc(ft_strlen(tmp) + 2, sizeof(char));
	ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
	free(tmp);
	return (str);
}

char			*preliminar_replacement(char *line, t_env enviro)
{
	int i;
	int k;
	int j;
	char *str;
	char *tmp;
	char *tmp2;
	t_doll dol;

	i = 0;
	k = 0;
	str = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	while (line[i] != '\0')
	{
		if (line[i] == '$')
		{
			j = 0;
			while (enviro.envp[j] != NULL)
			{
				set_len(&dol, enviro.envp[j], &line[i + 1]);
				if (ft_strncmp(&line[i + 1], enviro.envp[j], dol.len) == 0)
				{
					tmp = str;
					str = ft_strjoin(tmp, &enviro.envp[j][search_the_equal(enviro.envp[j]) + 1]); //check pour des " et '
					free(tmp);
					tmp = str;
					str = ft_calloc(ft_strlen(tmp) + ft_strlen(line), sizeof(char));
					ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
					free(tmp);
					str = re_back(k, str, &i, line);
					k = ft_strlen(str);
					i = i + dol.len + 1;
				}
				else if (enviro.envp[++j] == NULL && line[i + 1] == '?')
				{
					tmp2 = ft_itoa(enviro.lsc);
					tmp = str;
					str = ft_calloc(ft_strlen(tmp) + ft_strlen(tmp2) + 3, sizeof(char));
					ft_strlcpy(str, tmp, ft_strlen(tmp) + 1);
					free(tmp);
					ft_strlcpy(&str[k], tmp2, ft_strlen(tmp2) + 1);
					k = k + ft_strlen(tmp2);
					i = i + 2;
					free(tmp2);
				}
				else if (enviro.envp[j] == NULL)
					i = i + find_the_end_env(&line[i + 1]) + 1;
			}
		}
		str[k] = line[i];
		++i;
		++k;
	}
	return (prel_ending(str));
}

int				parse_exec
	(char *line, t_r_output redir, t_env *enviro, t_pipe *pip)
{
	char	**tabl;
	int		ret;
	char	*nl;

	if ((ret = hub_broken_quote(line, enviro)) != 0)
		return (ret);
	nl = preliminar_replacement(line, *enviro);
	tabl = ft_enhanced_split(nl, enviro);
	free(nl);
	if (is_builtin(tabl[0]) == 0)
		ret = builtin_caller(pip, tabl, enviro, redir);
	else if (tabl[0] != NULL && ft_strlen(tabl[0]) != 0)
		ret = search_and_exec(tabl, enviro, redir, pip);
	free_env(tabl);
	free(tabl);
	return (ret);
}
