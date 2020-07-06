#include "../head/minishell.h"

int fill_t_pipe(t_pipe *pip, char **p_tab)
{
	int n_pipe;

	pip->nbr = 0;
	pip->total = env_len(p_tab);
	n_pipe = 0;

	pip->pipefd = malloc((pip->total) * sizeof(int*));
	pip->pipefd[0] = NULL;
	if (pip->total < 2)
		return (0);
	while (n_pipe + 1 < pip->total)
	{
		pip->pipefd[n_pipe] = malloc(2 * sizeof(int));
		pipe(pip->pipefd[n_pipe]);
		++n_pipe;
	}
	pip->pipefd[n_pipe] = NULL;
	return (0);
}

int count_pipe(char *line)
{
	int i;
	int n_pipe;
	int quotes;

	i = 0;
	quotes = 0;
	n_pipe = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\'') && quotes == 0)
            quotes++;
        else if ((line[i] == '\"' || line[i] == '\'') && quotes == 1)
            quotes--;
		else if (line[i + 1] == '|' && line[i] != '\\' && quotes == 0)
			++n_pipe;
		i++;
	}
	return (n_pipe);
}

int len_line(char *line)
{
	int i;
	int l_line;
	int quotes;

	i = 0;
	quotes = 0;
	l_line = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '\"' || line[i] == '\'') && quotes == 0)
            quotes++;
        else if ((line[i] == '\"' || line[i] == '\'') && quotes == 1)
            quotes--;
		else if (line[i + 1] == '|' && line[i] != '\\' && quotes == 0)
			return (i + 2);
		i++;
	}
	return (i + 1);
}

void copy_word(char *src, char *dest)					//ICI LE PRBLM
{
	int i;
	int quotes;

	i = 0;
	quotes = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		if ((src[i] == '\"' || src[i] == '\'') && quotes == 0)
            quotes++;
        else if ((src[i] == '\"' || src[i] == '\'') && quotes == 1)
            quotes--;
		else if (src[i + 1] == '|' && src[i] != '\\' && quotes == 0)
			break;
		i++;
	}
	++i;						//possible prblm ici
	dest[i] = '\0';
}

int split_pipe(char *line, char ***attach)
{
	char **p_tab;
	int n_pipe;
	int i;
	int j;

	n_pipe = count_pipe(line) + 2;
	p_tab = malloc(n_pipe * sizeof(char*));
	i = 0;
	j = 0;
	while (i + 1 < n_pipe)
	{
		if (check_redir_error(&line[j]) == 1)
		{
			p_tab[i] = NULL;
			*attach = p_tab;
			return (1);
		}
		//printf("%d   %d\n", len_line(&line[j]), j);
		p_tab[i] = calloc(len_line(&line[j]) + 2, sizeof(char)); //GROSSE LIGNE DE MERDE TA GROSSE DARONNE LA
		copy_word(&line[j], p_tab[i]);	
		j = j + len_line(&line[j]);
		++i;
	}
	p_tab[i] = NULL;
	*attach = p_tab;
	return (0);
}
