/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 10:02:18 by delacourt         #+#    #+#             */
/*   Updated: 2019/10/14 16:10:15 by madelaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*str;

	i = 0;
	if (count == 0 || size == 0)
		return (NULL);
	if (!(str = malloc(size * count)))
		return (NULL);
	while (i < count)
	{
		((char *)str)[i] = '\0';
		i++;
	}
	return (str);
}
