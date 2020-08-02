/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_r_in_out2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 18:21:40 by velovo            #+#    #+#             */
/*   Updated: 2020/07/14 18:21:43 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

/*
**	utils function for the redirection > >> <
*/

int		ft_strlen_redirect(char *line, char red)
{
	int i;

	i = 0;
	while (line[i] && line[i] != red)
		i++;
	return (i);
}

void	close_redirect(t_r_output *redir)
{
	if (redir->out != 1 && redir->out != -1)
	{
		close(redir->out);
		redir->out = 1;
	}
	if (redir->in != 0 && redir->in != -1)
	{
		close(redir->in);
		redir->out = 0;
	}
	free(redir->ret);
}

char	*get_file_name(char *str, t_env *enviro)
{
	char	*tst;
	int		j;

	j = 0;
	tst = fill_word(str, enviro, &j, '$');
	return (tst);
}

int		check_redir_error(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		++i;
	if ((c == '|' && line[i] == '|') || (c == '>' && (line[i] == '<'
	|| line[i] == '>' || line[i] == ';' || line[i] == '|' || line[i] == 0)))
		return (1);
	return (0);
}
