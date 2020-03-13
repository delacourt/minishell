/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:26:24 by madelaco          #+#    #+#             */
/*   Updated: 2019/10/16 12:32:42 by delacourt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		malloc_arr(char ***arr, char *str, char c)
{
	int i;
	int r;

	i = 0;
	r = 1;
	while (str[i])
	{
		if (str[i] == c)
		{
			r++;
			i++;
			while (str[i] == c)
				i++;
		}
		else
			i++;
	}
	if (!(*arr = malloc(sizeof(**arr) * (r + 1))))
		return (0);
	return (1);
}

int		malloc_str(char **arr_k, char ***arr, int j)
{
	int i;

	i = 0;
	if (!(*arr_k = malloc(sizeof(char) * (j))))
	{
		while (*arr[i])
			free(*arr[i++]);
		free(*arr);
		return (0);
	}
	return (1);
}

void	str_malloc(char *str, char c, char **arr)
{
	int k;
	int j;

	k = 0;
	j = 0;
	while (*str)
	{
		while ((*str == c) && *str)
			str++;
		if (!(*str == c) && *str)
		{
			if (k > 0)
				malloc_str(&arr[k - 1], &arr, (j + 1));
			j = (k++ > 0) ? 0 : j;
		}
		while (!(*str == c) && *str)
		{
			j++;
			str++;
		}
	}
	if (k > 0)
		malloc_str(&arr[k - 1], &arr, (j + 1));
	arr[k] = malloc(sizeof(NULL));
}

char	**ft_split(char const *str, char c)
{
	int		j;
	int		k;
	char	**arr;

	malloc_arr(&arr, (char *)str, c);
  str_malloc((char *)str, c, arr);
  j = 0;
	k = 0;
	while (*str)
	{
		while ((*str == c) && *str)
			str++;
		if (!(*str == c) && *str)
		{
			if (k > 0)
				arr[k - 1][j] = '\0';
			j = (k++ > 0) ? 0 : j;
		}
		while (!(*str == c) && *str)
			arr[k - 1][j++] = *(str++);
	}
	if (k > 0)
		arr[k - 1][j] = '\0';
	arr[k] = NULL;
	return (arr);
}
