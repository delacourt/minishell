/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:01:18 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/14 15:06:17 by madelaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		trim_len(char *s1, char *set)
{
	int i;
	int r;

	i = 0;
	r = 0;
	while (char_in_str(s1[i], set))
		i++;
	while (s1[i++])
		r++;
	i = i - 2;
	while (i >= 0 && char_in_str(s1[i], set))
	{
		r--;
		i--;
	}
	return (r + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	size = trim_len((char *)s1, (char *)set);
	if (size <= 0)
		size = 1;
	if (!(str = malloc(sizeof(char) * size)))
		return (NULL);
	while (char_in_str(s1[i], (char *)set))
		i++;
	while (j < size - 1)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
