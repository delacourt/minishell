/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:41:48 by velovo            #+#    #+#             */
/*   Updated: 2020/07/15 18:42:34 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

int		inter_line(char **line, t_env *enviro)
{
	int		k;
	t_read	t_r;
	t_key	key;
	int		end = 0;
	char	c_key[4] = {0, 0, 0, 0};

	t_r.ou = 1;
	fill(&key);
	t_r.c_key = c_key;
	t_r.tst = ft_calloc(2, sizeof(char));
	while (1)
	{
		t_r.t = 0;
		read(0, &t_r.t, 1);
		if((t_r.t >= 32 && t_r.t <= 126) && ft_strlen(c_key) == 0)
		{
			t_r.hold = ft_strdup(t_r.tst);
			t_r.tmp = t_r.tst;
			t_r.tst = ft_calloc(ft_strlen(t_r.hold) + 2, sizeof(char));
			free(t_r.tmp);
			ft_strlcpy(t_r.tst, t_r.hold, ft_strlen(t_r.hold) + 1);
			test1213(t_r.tst, end, t_r.t);
			++end;
			free(t_r.hold);
		}
		if (t_r.t == 27 || ft_strlen(c_key) > 0)
		{
			c_key[ft_strlen(c_key)] = t_r.t;
		}
		if (t_r.t == '\n')
		{
			put_in_histo(enviro, t_r.tst);
			*line = t_r.tst;
			return (1);
		}
		else if (t_r.t == 4 && ft_strlen(t_r.tst) == 0) //ctrl D
			exit(0);
		else if (t_r.t == 3) //ctrl C
		{
			write(1, "^C\n", 3);
			ft_memset(t_r.tst, 0, ft_strlen(t_r.tst));
			end = 0;
			enviro->lsc = 1;
			print_new_line(enviro->lsc);
		}
		else if (t_r.t == 28) //ctrl backslash
			;
		else if (ft_strncmp(c_key, key.g, 4) == 0)
			k_left(key, &end, &t_r);
		else if (ft_strncmp(c_key, key.d, 4) == 0)
			k_right(key, &end, &t_r);
		else if (ft_strncmp(c_key, key.h, 4) == 0)
			k_up(enviro, &t_r, key, &end);
		else if (ft_strncmp(c_key, key.b, 4) == 0)
			k_down(enviro, &t_r, key, &end);
		else if (t_r.t == 127 && end > 0)
		{
			ft_strlcpy(&t_r.tst[end - 1], &t_r.tst[end], ft_strlen(&t_r.tst[end]) + 1);
			end = end - 1;
			write(1, &key.g, 3);
			write(1, &t_r.tst[end], ft_strlen(&t_r.tst[end]));
			write(1, " ", 1);
			for (int j = 0; j <= ft_strlen(&t_r.tst[end]); ++j)
				write(1, &key.g, 3);
		}
		else if (ft_strlen(c_key) == 0 && (t_r.t >= 32 && t_r.t <= 126))
		{
			write(1, &t_r.t, 1);
			write(1, &t_r.tst[end], ft_strlen(&t_r.tst[end]));
			for (int i = 0; i < ft_strlen(&t_r.tst[end]); ++i)
				write(1, &key.g, 3);
		}
		if (ft_strlen(c_key) >= 3)
			ft_memset(c_key, 0, 4);
	}
}
