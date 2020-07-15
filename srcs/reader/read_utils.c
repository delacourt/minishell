/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:13:28 by velovo            #+#    #+#             */
/*   Updated: 2020/07/15 18:14:02 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

/*
**	setup the arrow key
*/

void	fill(t_key *key)
{
	key->g[0] = 27;
	key->g[1] = 91;
	key->g[2] = 68;
	key->g[3] = 0;
	key->d[0] = 27;
	key->d[1] = 91;
	key->d[2] = 67;
	key->d[3] = 0;
	key->h[0] = 27;
	key->h[1] = 91;
	key->h[2] = 65;
	key->h[3] = 0;
	key->b[0] = 27;
	key->b[1] = 91;
	key->b[2] = 66;
	key->b[3] = 0;
}

/*
**	put the given line in the historic
*/

void	put_in_histo(t_env *enviro, char *tst)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 9;
	enviro->histo[0] = tst;
	while (i >= 0)
	{
		enviro->histo[i + 1] = enviro->histo[i];
		--i;
	}
	if (enviro->histo[10] != NULL)
	{
		free(enviro->histo[10]);
		enviro->histo[10] = NULL;
	}
}

/*
**	put the given caracter at the right place in the string
*/

void	test1213(char *tst, int len, char c)
{
	char	*tmp;

	tmp = ft_strdup(&tst[len]);
	tst[len] = c;
	ft_strlcpy(&tst[len + 1], tmp, ft_strlen(tmp) + 1);
	free(tmp);
}
