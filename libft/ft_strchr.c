/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 12:07:41 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/16 12:25:29 by delacourt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;
	int	size;

	i = 0;
	size = (int)ft_strlen(str);
	while (i <= size)
	{
		if (str[i] == c)
			return (&((char *)str)[i]);
		i++;
	}
	return (0);
}
