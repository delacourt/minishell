/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 16:52:58 by avan-pra          #+#    #+#             */
/*   Updated: 2020/07/20 16:52:59 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

int		get_the_line(t_inter_read *term, char **line, t_env *enviro)
{
	int i;

	tcsetattr(0, 0, &term->s_set);
	i = inter_line(line, enviro);
	tcsetattr(0, 0, &term->backup);
	write(1, "\n", 1);
	return (i);
}

void	split_pipe_error(int *error, t_env *enviro, t_pipe *pip, char **p_tab)
{
	if (*error > 0)
	{
		enviro->lsc = 1;
		if (*error == 1)
			write(2, "mash: syntax error, unexpected token\n", 37);
		else if (*error == 2)
			write(2, "mash: 511 pipes+ aren't allowed\n", 32);
		*error = 1;
	}
	fill_t_pipe(pip, p_tab);
	pip->founded = pip->total;
	pip->pid = ft_calloc(pip->total, sizeof(int));
}

void	split_r_in_out_error(int *error, t_env *enviro, t_pipe *pip)
{
	if (*error > 0)
	{
		enviro->lsc = 1;
		--pip->founded;
		if (*error == 1)
			write(2, "mash: syntax error, unexpected token\n", 37);
		*error = 1;
	}
}
