/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:18:43 by velovo            #+#    #+#             */
/*   Updated: 2020/07/14 17:19:37 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

/*
**	return 0 or -1 if the string is not properly quoted
*/

static int	next_quote(char quote, int i, char *line)
{
	if (quote == '\"')
	{
		++i;
		while (line[i] != '\"' && line[i] != '\0')
		{
			if (line[i] == '\\')
				++i;
			++i;
		}
		return (i);
	}
	else
	{
		++i;
		while (line[i] != '\'' && line[i] != '\0')
		{
			if (line[i] == '\\' && line[i + 1] != '\'')
				++i;
			++i;
		}
		return (i);
	}
	return (i);
}

int			is_broken_quote(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '\"')
			i = next_quote('\"', i, line);
		else if (line[i] == '\'')
			i = next_quote('\'', i, line);
		else if (line[i] == '\\')
			++i;
		if (line[i] == '\0')
			return (1);
		++i;
	}
	return (0);
}
