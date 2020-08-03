/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 14:20:01 by avan-pra          #+#    #+#             */
/*   Updated: 2020/07/17 14:20:02 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

/*
**	utils for the split pipe funtion
*/

int		fill_t_pipe(t_pipe *pip, char **p_tab)
{
	int n_pipe;

	pip->nbr = 0;
	pip->total = env_len(p_tab);
	n_pipe = 0;
	if (!(pip->pipefd = malloc((pip->total) * sizeof(int*))))
		return (0);
	pip->pipefd[0] = NULL;
	if (pip->total < 2)
		return (0);
	while (n_pipe + 1 < pip->total)
	{
		pip->pipefd[n_pipe] = ft_calloc(2, sizeof(int));
		pipe(pip->pipefd[n_pipe]);
		++n_pipe;
	}
	pip->pipefd[n_pipe] = NULL;
	return (0);
}

int		count_pipe(char *line)
{
	int i;
	int n_pipe;
	int quotes;

	i = 0;
	quotes = 0;
	n_pipe = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\'') && quotes == 0)
			quotes++;
		else if ((line[i] == '\"' || line[i] == '\'') && quotes == 1)
			quotes--;
		else if (line[i + 1] == '|' && line[i] != '\\' && quotes == 0)
			++n_pipe;
		i++;
	}
	return (n_pipe);
}

int		len_line(char *line)
{
	int i;
	int l_line;
	int quotes;

	i = 0;
	quotes = 0;
	l_line = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\'') && quotes == 0)
			quotes++;
		else if ((line[i] == '\"' || line[i] == '\'') && quotes == 1)
			quotes--;
		else if (line[i + 1] == '|' && line[i] != '\\' && quotes == 0)
			return (i + 2);
		i++;
	}
	return (i + 1);
}

void	copy_word(char *src, char *dest)
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		if ((src[i] == '\"' || src[i] == '\'') && quotes == 0)
			quotes++;
		else if ((src[i] == '\"' || src[i] == '\'') && quotes == 1)
			quotes--;
		else if (src[i + 1] == '|' && src[i] != '\\' && quotes == 0)
			break ;
		i++;
	}
	++i;
	dest[i] = '\0';
}
