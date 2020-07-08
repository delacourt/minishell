/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_r_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 16:35:57 by delacourt         #+#    #+#             */
/*   Updated: 2020/07/06 17:19:32 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/minishell.h"

int     ft_strlen_redirect(char *line, char red)
{
    int i;

    i = 0;
    while (line[i] && line[i] != red)
        i++;
    return (i);
}

void    close_redirect(t_r_output *redir)
{
    if (redir->out != 1)
    {
		close(redir->out);
		redir->out = 1;
	}
	if (redir->in != 0)
	{
		close(redir->in);
		redir->out = 0;
	}
    free(redir->ret);
}

char    *get_file_name(char *str, t_env *enviro)
{
	char *tst;
	
	tst = fill_word(str, enviro);
	return (tst);							//il faut free tst
}

int check_redir_error(char *line, char c)
{
	int i = 0;

	while (line[i] == ' ')
		++i;
	if ((c == '|' && line[i] == '|') || (c == '>' && (line[i] == '<' || line[i] == '>' || line[i] == ';' || line[i] == '|')))
		return (1);
	return (0);
}

int     split_r_in_out(char *line, t_r_output *redir, t_env *enviro)
{
    int i;
    int j;
    int quotes;
	char *filename;
	int lt = 0;

	//printf("%s\n", line);
    i = 0;
    j = 0;
    quotes = 0;
    redir->out = 1;
	redir->in = 0;
    redir->ret = calloc(ft_strlen(line) + 1, sizeof(char)); //ft_calloc
	//printf("%zu\n", ft_strlen(line));
	while (line[i] != '\0')
    {
        //printf("%zu     %d     %d\n", ft_strlen(line), i, line[i]);

		// if (lt == 0)
		// 	redir->ret[j++] = line[i]
		lt = 0;
		if ((line[i] == '\"' || line[i] == '\'') && quotes == 0)
            quotes++;
        else if ((line[i] == '\"' || line[i] == '\'') && quotes == 1)
            quotes--;
        else if ((i == 0 && line[i] == '>' && line[i + 1] != '>') || (line[i] == '>' && line[i - 1] != '\\' && quotes == 0 && line[i + 1] != '>'))
      	//else if (line[i + 1] == '>' && line[i] != '\\' && quotes == 0 && line[i + 2] != '>')
        {
			if (check_redir_error(&line[i + 1], '>') == 1)
				return (1);
			if (redir->out != 1)
				close(redir->out);
			filename = get_file_name(&line[i + 1], enviro);
			redir->out = open(filename, O_WRONLY | O_TRUNC | O_CREAT); //faire des checks si -1 et free
			if (redir->out == -1)
			{
				free(filename);
				write(2, "mash: permission denied\n", 24);
				return (2);
			}
			free(filename);
			i = i + 1;
			i = i + advance(&line[i]);
			if (line[i] == '<' || line[i] == '>')
				--i;
			//--i;
			lt = 1;
        }
        //else if (line[i + 1] == '>' && line[i] != '\\' && quotes == 0 && line[i + 2] == '>')
        else if ((i == 0 && line[i] == '>' && line[i + 1] == '>') || (line[i] == '>' && line[i - 1] != '\\' && quotes == 0 && line[i + 1] == '>'))
		{
            if (check_redir_error(&line[i + 2], '>') == 1)
				return (1);
			if (redir->out != 1)
				close(redir->out);
            filename = get_file_name(&line[i + 2], enviro);
			redir->out = open(filename, O_WRONLY | O_APPEND | O_CREAT); //faire des checks si -1 et free
			if (redir->out == -1)
			{
				free(filename);
				write(2, "mash: permission denied\n", 24);
				return (2);
			}
			free(filename);
			i = i + 2;
			i = i + advance(&line[i]);
			//--i;
			lt = 1;
			//break;
        }
        else if ((i == 0 && line[i] == '<') || (line[i] == '<' && line[i - 1] != '\\' && quotes == 0))
		//else if (line[i + 1] == '<' && line[i] != '\\' && quotes == 0)
        {
            if (check_redir_error(&line[i + 1], '>') == 1)
				return (1);
			if (redir->in != 0)
				close(redir->in);
            filename = get_file_name(&line[i + 1], enviro);
			redir->in = open(filename, O_RDONLY); //faire des checks si -1 et free
			if (redir->in == -1)
			{
				free(filename);
				write(2, "mash: permission denied\n", 24);
				return (2);
			}
			free(filename);
			i = i + 1;
			i = i + advance(&line[i]);
			if (line[i] == '<' || line[i] == '>')
				--i;
			//--i;
			lt = 1;
			//break;
        }
		redir->ret[j] = line[i];
        j++;
		i++;
    }
	//printf("in:%d\nout:%d\n%s\n", redir->in, redir->out, redir->ret);
    return (0);
}
