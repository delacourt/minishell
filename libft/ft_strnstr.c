/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 09:37:45 by delacourt         #+#    #+#             */
/*   Updated: 2019/10/14 14:47:23 by madelaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haysack, const char *needle, size_t len)
{
	size_t i;
	size_t j;

	j = 0;
	if (needle[j] == '\0')
		return ((char *)haysack);
	while (haysack[j])
	{
		i = 0;
		while (haysack[i + j] == needle[i] && (i + j) < len)
		{
			if (needle[i + 1] == '\0')
				return ((char *)haysack + j);
			i++;
		}
		j++;
	}
	return (0);
}
