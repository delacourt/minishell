/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_event2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:16:42 by velovo            #+#    #+#             */
/*   Updated: 2020/07/16 14:16:44 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

int		k_enter(t_env *enviro, char **line, t_read *t_r)
{
	put_in_histo(enviro, t_r->tst);
	*line = t_r->tst;
	return (1);
}

void	k_ctrl_c(t_env *enviro, t_read *t_r, int *end)
{
	write(1, "^C\n", 3);
	ft_memset(t_r->tst, 0, ft_strlen(t_r->tst));
	*end = 0;
	enviro->lsc = 1;
	print_new_line(enviro->lsc);
}

void	k_normal(t_read *t_r, int *end)
{
	t_r->hold = ft_strdup(t_r->tst);
	t_r->tmp = t_r->tst;
	t_r->tst = ft_calloc(ft_strlen(t_r->hold) + 2, sizeof(char));
	free(t_r->tmp);
	ft_strlcpy(t_r->tst, t_r->hold, ft_strlen(t_r->hold) + 1);
	put_char_in_str(t_r->tst, *end, t_r->t);
	++*end;
	free(t_r->hold);
}

void	k_del(t_read *t_r, int *end, t_key key)
{
	int j;

	ft_strlcpy(&t_r->tst[*end - 1], &t_r->tst[*end],
		ft_strlen(&t_r->tst[*end]) + 1);
	*end = *end - 1;
	write(1, &key.g, 3);
	write(1, &t_r->tst[*end], ft_strlen(&t_r->tst[*end]));
	write(1, " ", 1);
	j = 0;
	while (j <= ft_strlen(&t_r->tst[*end]))
	{
		write(1, &key.g, 3);
		++j;
	}
}

void	write_char(t_read *t_r, int *end, t_key key)
{
	int i;

	write(1, &t_r->t, 1);
	write(1, &t_r->tst[*end], ft_strlen(&t_r->tst[*end]));
	i = 0;
	while (i < ft_strlen(&t_r->tst[*end]))
	{
		write(1, &key.g, 3);
		++i;
	}
}
