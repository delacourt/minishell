/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_semi_colon.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 11:05:15 by delacourt         #+#    #+#             */
/*   Updated: 2020/04/01 09:55:31 by delacourt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

static int		count_semi_colon(char *line)
{
	int	sc;
	int	i;
	int	q;

	i = 0;
	q = 0;
	sc = 0;
	while (line[i])
	{
		if (line[i] == '\"' && q == 0)
			q++;
		else if (line[i] == '\"' && q == 1)
			q--;
		if (line[i + 1] == ';' && line[i] != '\\' && q == 0)
			sc++;
		i++;
	}
	return (sc);
}

void			setup_t_split_sc(t_split_sc *split)
{
	split->line_i = 0;
	split->line_j = 0;
	split->line_const = 0;
	split->tabl_i = 0;
	split->tabl_j = 0;
	split->quote = 0;
}

void			reset_values_loop(t_split_sc *split)
{
	split->tabl[split->tabl_i][split->tabl_j] = '\0';
	split->tabl_j = 0;
	split->line_j = -1;
	split->tabl_i++;
	split->line_const++;
	split->line_i++;
}

void			split_line_loop(char *line, t_split_sc *split)
{
	while (line[split->line_i])
	{
		if (line[split->line_i] == '\"' && split->quote == 0)
			split->quote++;
		else if (line[split->line_i] == '\"' && split->quote == 1)
			split->quote--;
		if (line[split->line_i + 1] == ';'
			&& line[split->line_i] != '\\' && split->quote == 0)
		{
			split->tabl[split->tabl_i] = ft_calloc((split->line_j + 2),
										sizeof(char));
			while (split->line_const <= split->line_i)
			{
				split->tabl[split->tabl_i]
							[split->tabl_j] = line[split->line_const];
				split->line_const++;
				split->tabl_j++;
			}
			reset_values_loop(split);
		}
		split->line_j++;
		split->line_i++;
	}
}

char			**split_semi_colon(char *line)
{
	t_split_sc split;

	setup_t_split_sc(&split);
	split.tabl = ft_calloc((count_semi_colon(line) + 2), sizeof(char *));
	split_line_loop(line, &split);
	split.line_j--;
	split.tabl[split.tabl_i] = ft_calloc((split.line_j + 2), sizeof(char));
	while (split.line_const < split.line_i)
	{
		split.tabl[split.tabl_i][split.tabl_j] = line[split.line_const];
		split.line_const++;
		split.tabl_j++;
	}
	split.tabl[split.tabl_i][split.tabl_j] = '\0';
	split.tabl_i++;
	split.tabl[split.tabl_i] = NULL;
	return (split.tabl);
}
