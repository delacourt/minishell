/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 17:18:43 by velovo            #+#    #+#             */
/*   Updated: 2020/07/14 17:19:37 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

int		is_broken_pipe(char *str)
{
	int quote;
	int i;

	quote = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\\')
			++i;
		else if ((str[i] == '\"' || str[i] == '\'') && quote == 0)
			++quote;
		else if ((str[i] == '\"' || str[i] == '\'') && quote == 1)
			--quote;
		else if (str[i] == '|' && quote == 0 && is_empty_line(&str[i + 1], ' ') == 0)
			return (1);
		++i;
	}
	return (0);
}
