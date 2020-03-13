/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelaco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:01:16 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/14 14:31:54 by madelaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*str_t;
	unsigned char	c_t;

	i = 0;
	c_t = (unsigned char)c;
	str_t = (unsigned char *)str;
	while (i < n)
	{
		str_t[i] = c_t;
		i++;
	}
	return (str);
}
