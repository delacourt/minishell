/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_r_in_out1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:35:57 by delacourt         #+#    #+#             */
/*   Updated: 2020/07/14 18:30:19 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

int				split_r_in_out(char *line, t_r_output *redir, t_env *enviro)
{
	int			i;
	int			j;
	int			quotes;
	char		*filename;
	t_etup_i_o	giv;

	giv.i = &i;
	giv.quotes = &quotes;
	i = 0;
	j = 0;
	quotes = 0;
	redir->out = 1;
	redir->in = 0;
	redir->ret = ft_calloc(ft_strlen(line) + 1, sizeof(char));
	while (line[i] != '\0')
	{
		giv.ret = fd_checker(line, &giv, redir, enviro);
		if (giv.ret > 0)
			return (giv.ret);
		redir->ret[j] = line[i];
		j++;
		i++;
	}
	return (0);
}
