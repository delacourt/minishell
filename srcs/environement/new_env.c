/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 15:31:58 by velovo            #+#    #+#             */
/*   Updated: 2020/07/16 15:32:09 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

char	**new_env_variable(char *str, char **envp)
{
	char	**newenvp;
	int		i;

	i = 0;
	newenvp = malloc((env_len(envp) + 2) * sizeof(char*));
	while (envp[i] != NULL)
	{
		newenvp[i] = malloc((ft_strlen(envp[i]) + 1) * sizeof(char));
		ft_strlcpy(newenvp[i], envp[i], ft_strlen(envp[i]) + 1);
		free(envp[i]);
		++i;
	}
	newenvp[i] = malloc((ft_strlen(str) + 1) * sizeof(char));
	ft_strlcpy(newenvp[i], str, ft_strlen(str) + 1);
	++i;
	newenvp[i] = NULL;
	free(envp);
	return (newenvp);
}

void	exisiting_env_variable(t_env *enviro, int *found, char *arg, int s)
{
	int j;

	j = 0;
	while (enviro->envp[j] != NULL && *found == 0)
	{
		if (ft_strncmp(arg, enviro->envp[j], s) == 0)
		{
			*found = 1;
			free(enviro->envp[j]);
			enviro->envp[j] = malloc((ft_strlen(arg) + 1)
				* sizeof(char));
			ft_strlcpy(enviro->envp[j], arg, ft_strlen(arg) + 1);
		}
		++j;
	}
}

char	**export_new(char **arg, t_env *enviro)
{
	int i;
	int s;
	int found;

	i = 0;
	enviro->lsc = 0;
	while (arg[i] != NULL)
	{
		s = search_the_equal(arg[i]);
		if (s == -1)
		{
			write(1, "mash: bad assignment\n", 21);
			enviro->lsc = 1;
			break ;
		}
		found = 0;
		exisiting_env_variable(enviro, &found, arg[i], s);
		if (found == 0)
			enviro->envp = new_env_variable(arg[i], enviro->envp);
		++i;
	}
	return (enviro->envp);
}
