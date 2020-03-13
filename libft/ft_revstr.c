/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelaco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:17:34 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/09 15:18:35 by madelaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_revstr(char *str)
{
	char	t;
	int		i;
	int		j;
	int		size;

	size = 0;
	while (str[size])
		size++;
	i = size - 1;
	j = 0;
	while (i > j)
	{
		t = str[i];
		str[i] = str[j];
		str[j] = t;
		j++;
		i--;
	}
}
