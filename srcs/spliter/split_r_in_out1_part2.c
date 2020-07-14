/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_r_in_out1_part2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 19:48:54 by velovo            #+#    #+#             */
/*   Updated: 2020/07/14 19:48:55 by velovo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../head/minishell.h"

static int		set_output(char *line, int *i, t_r_output *redir, t_env *enviro)
{
	char *filename;

	if (check_redir_error(&line[*i + 1], '>') == 1)
		return (1);
	if (redir->out != 1)
		close(redir->out);
	filename = get_file_name(&line[*i + 1], enviro);
	redir->out = open(filename, O_WRONLY | O_TRUNC | O_CREAT);
	if (redir->out == -1)
	{
		free(filename);
		write(2, "mash: permission denied\n", 24);
		return (2);
	}
	free(filename);
	*i = *i + 1;
	*i = *i + advance(&line[*i]);
	if (line[*i] == '<' || line[*i] == '>')
		--*i;
	return (0);
}

static int		set_double_output(char *line, int *i,
	t_r_output *redir, t_env *enviro)
{
	char *filename;

	if (check_redir_error(&line[*i + 2], '>') == 1)
		return (1);
	if (redir->out != 1)
		close(redir->out);
	filename = get_file_name(&line[*i + 2], enviro);
	redir->out = open(filename, O_WRONLY | O_APPEND | O_CREAT);
	if (redir->out == -1)
	{
		free(filename);
		write(2, "mash: permission denied\n", 24);
		return (2);
	}
	free(filename);
	*i = *i + 2;
	*i = *i + advance(&line[*i]);
	return (0);
}

static int		set_input(char *line, int *i, t_r_output *redir, t_env *enviro)
{
	char *filename;

	if (check_redir_error(&line[*i + 1], '>') == 1)
		return (1);
	if (redir->in != 0)
		close(redir->in);
	filename = get_file_name(&line[*i + 1], enviro);
	redir->in = open(filename, O_RDONLY);
	if (redir->in == -1)
	{
		free(filename);
		write(2, "mash: permission denied\n", 24);
		return (2);
	}
	free(filename);
	*i = *i + 1;
	*i = *i + advance(&line[*i]);
	if (line[*i] == '<' || line[*i] == '>')
		--*i;
	return (0);
}

int				fd_checker_next(char *line,
	t_etup_i_o *giv, t_r_output *redir, t_env *enviro)
{
	if ((*giv->i == 0 && line[*giv->i] == '>' && line[*giv->i + 1] != '>')
	|| (line[*giv->i] == '>' && line[*giv->i - 1] != '\\'
	&& *giv->quotes == 0 && line[*giv->i + 1] != '>'))
	{
		giv->ret = set_output(line, giv->i, redir, enviro);
		if (giv->ret > 0)
			return (giv->ret);
	}
	else if ((*giv->i == 0 && line[*giv->i] == '>' && line[*giv->i + 1] == '>')
	|| (line[*giv->i] == '>' && line[*giv->i - 1] != '\\'
	&& *giv->quotes == 0 && line[*giv->i + 1] == '>'))
	{
		giv->ret = set_double_output(line, giv->i, redir, enviro);
		if (giv->ret > 0)
			return (giv->ret);
	}
	else if ((*giv->i == 0 && line[*giv->i] == '<')
	|| (line[*giv->i] == '<' && line[*giv->i - 1] != '\\' && *giv->quotes == 0))
	{
		giv->ret = set_input(line, giv->i, redir, enviro);
		if (giv->ret > 0)
			return (giv->ret);
	}
	return (0);
}

int				fd_checker(char *line,
	t_etup_i_o *giv, t_r_output *redir, t_env *enviro)
{
	if ((line[*giv->i] == '\"' || line[*giv->i] == '\'') && giv->quotes == 0)
		++*giv->quotes;
	else if ((line[*giv->i] == '\"'
		|| line[*giv->i] == '\'') && *giv->quotes == 1)
		--*giv->quotes;
	else
		fd_checker_next(line, giv, redir, enviro);
	return (0);
}
