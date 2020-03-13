/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:09:18 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/14 14:33:46 by madelaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(char *s, size_t n)
{
	size_t			i;
	unsigned char	*str_t;

	i = 0;
	str_t = (unsigned char *)s;
	while (i < n)
	{
		str_t[i] = '\0';
		i++;
	}
}
