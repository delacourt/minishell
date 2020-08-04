/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 17:43:15 by avan-pra          #+#    #+#             */
/*   Updated: 2020/08/03 17:43:16 by avan-pra         ###   ########.fr       */
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
		if (line[i] == '\0')
			return (1);
		if (line[i] == '\\')
			++i;
		++i;
	}
	return (0);
}
