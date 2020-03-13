/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madelaco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 09:46:33 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/14 15:04:49 by madelaco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	return_value(unsigned long n, int s)
{
	if ((n > 2147483647) && (s == 1))
		return (-1);
	if ((n > 2147483648) && (s == -1))
		return (0);
	return ((int)n * s);
}

int	signe_atoi(char *str, int *i)
{
	int s;

	s = 1;
	if (str[*i] == '-')
	{
		s = -1;
		*i += 1;
	}
	else if (str[*i] == '+')
		*i += 1;
	return (s);
}

int	ft_atoi(const char *str)
{
	int				i;
	int				s;
	int				min;
	unsigned long	n;
	unsigned long	d;

	i = 0;
	d = 1;
	n = 0;
	while (str[i] == 32 || ((str[i] > 8) && (str[i] < 14)))
		i++;
	s = signe_atoi((char *)str, &i);
	min = i;
	while (ft_isdigit(str[i]))
		i++;
	i--;
	while (i >= min)
	{
		n += (str[i--] - '0') * d;
		d *= 10;
	}
	return (return_value(n, s));
}
