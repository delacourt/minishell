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

/*
**	check all special keyin order, this function will check:
**
**		ctrl D		exit() tention
**		ctrl C
**		ctrl backslash (ne fait rien actuellement)
**		fleche gauche
**		fleche droite
**		fleche du haut
**		fleche du bas
**		touche delete
**		marquer le caractere si il est ok
*/

void	check_key(t_env *enviro, t_read *t_r, int *end, t_key key)
{
	if (t_r->t == 4 && ft_strlen(t_r->tst) == 0)
		exit(0);
	else if (t_r->t == 3)
		k_ctrl_c(enviro, t_r, end);
	else if (t_r->t == 28)
		;
	else if (ft_strncmp(t_r->c_key, key.g, 4) == 0)
		k_left(key, end, t_r);
	else if (ft_strncmp(t_r->c_key, key.d, 4) == 0)
		k_right(key, end, t_r);
	else if (ft_strncmp(t_r->c_key, key.h, 4) == 0)
		k_up(enviro, t_r, key, end);
	else if (ft_strncmp(t_r->c_key, key.b, 4) == 0)
		k_down(enviro, t_r, key, end);
	else if (t_r->t == 127 && *end > 0)
		k_del(t_r, end, key);
	else if (ft_strlen(t_r->c_key) == 0 && (t_r->t >= 32 && t_r->t <= 126))
		write_char(t_r, end, key);
}

/*
**	setup function for the read
*/

void	setup_read(t_key *key, t_read *t_r, char c_key[4], int *end)
{
	*end = 0;
	t_r->c_key = c_key;
	ft_memset(t_r->c_key, 0, 4);
	t_r->ou = 1;
	fill_key(key);
	t_r->tst = ft_calloc(2, sizeof(char));
}

/*
**	main function for the read()
**	check for normal key (abcdef/etc...)
**	fill directionnal key if one was pressed
**	enter key
**	check for all other key
**	reset special key (to not segfault (shift + directionnal key))
*/

int		inter_line(char **line, t_env *enviro)
{
	int		k;
	t_read	t_r;
	t_key	key;
	int		end;
	char	c_key[4];

	setup_read(&key, &t_r, c_key, &end);
	while (1)
	{
		t_r.t = 0;
		read(0, &t_r.t, 1);
		if ((t_r.t >= 32 && t_r.t <= 126) && ft_strlen(c_key) == 0)
			k_normal(&t_r, &end);
		if (t_r.t == 27 || ft_strlen(c_key) > 0)
			c_key[ft_strlen(c_key)] = t_r.t;
		if (t_r.t == '\n')
			return (k_enter(enviro, line, &t_r));
		else
			check_key(enviro, &t_r, &end, key);
		if (ft_strlen(c_key) >= 3)
			ft_memset(c_key, 0, 4);
	}
}
