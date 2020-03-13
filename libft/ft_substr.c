/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:20:36 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/16 12:27:12 by delacourt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > (unsigned int)ft_strlen(s))
		len = 0;
	if (!(sub_str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len && s[i])
	{
		sub_str[i++] = s[start++];
	}
	sub_str[i] = '\0';
	return (sub_str);
}
