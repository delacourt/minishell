/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 21:15:49 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/16 12:26:22 by delacourt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t scrsize;

	scrsize = 0;
	while (dst[scrsize] && scrsize < dstsize)
		scrsize += 1;
	i = scrsize;
	while (src[scrsize - i] && scrsize + 1 < dstsize)
	{
		dst[scrsize] = src[scrsize - i];
		scrsize += 1;
	}
	if (i < dstsize)
		dst[scrsize] = '\0';
	return (i + ft_strlen(src));
}
