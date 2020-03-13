/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelaco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:03:04 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/10 08:41:56 by madelaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		size_array(int n)
{
	int		r;
	long	nbr;

	r = 0;
	nbr = (long)n;
	if (nbr == 0)
		return (2);
	if (nbr < 0)
	{
		r++;
		nbr = nbr * -1;
	}
	while (nbr > 0)
	{
		r++;
		nbr /= 10;
	}
	return (r + 1);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	nbr;

	i = 0;
	nbr = (long)n;
	if (!(str = malloc(sizeof(char) * size_array(n))))
		return (NULL);
	if (nbr == 0)
		str[i++] = '0';
	if (nbr < 0)
		nbr = nbr * -1;
	while (nbr > 0)
	{
		str[i++] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		str[i++] = '-';
	str[i] = '\0';
	ft_revstr(str);
	return (str);
}
