/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelaco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:09:38 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/10 11:56:24 by madelaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_t;
	unsigned char	*src_t;
	size_t			i;

	dst_t = (unsigned char *)dst;
	src_t = (unsigned char *)src;
	i = 0;
	if (src_t < dst_t)
	{
		i = len;
		while (i > 0)
		{
			dst_t[i - 1] = src_t[i - 1];
			i--;
		}
	}
	if (src_t > dst_t)
		ft_memcpy(dst, src, len);
	return (dst);
}
