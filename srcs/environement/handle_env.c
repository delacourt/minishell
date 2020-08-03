/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:29:43 by velovo            #+#    #+#             */
/*   Updated: 2020/07/16 15:29:53 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

/*
**	will copy the given environement into a new one to be able to modify it
**	+ some utils function
*/

int		search_the_equal(char *str)
{
	int i;

	i = 0;
	if (str[i] == '=')
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		else if (str[i] == ' ')
			return (-1);
		++i;
	}
	return (-1);
}

void	free_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		++i;
	}
}

int		env_len(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
		++i;
	return (i);
}

static void		inc_shlvl(char **envp)
{
	int		lvl;
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp("SHLVL=", envp[i], 6) == 0)
		{
			lvl = ft_atoi((envp[i]) + 6);
			lvl++;
			free(envp[i]);
			tmp = ft_itoa(lvl);
			envp[i] = ft_strjoin("SHLVL=", tmp);
			free(tmp);
		}
		++i;
	}
}

char	**new_env(char **envp)
{
	char	**tenv;
	int		i;

	if (!(tenv = malloc((env_len(envp) + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		if (!(tenv[i] = malloc((ft_strlen(envp[i]) + 1) * sizeof(char))))
			return (NULL);
		ft_strlcpy(tenv[i], envp[i], ft_strlen(envp[i]) + 1);
		++i;
	}
	tenv[i] = NULL;
	inc_shlvl(tenv);
	return (tenv);
}
