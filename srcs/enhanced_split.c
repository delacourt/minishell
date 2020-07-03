#include "../head/minishell.h"

void	*free_arr(char **tabl, int j)
{
	while (j >= 0)
	{
		free(tabl[j]);
		j--;
	}
	free(tabl);
	return (NULL);
}

static int	count_split(const char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		// printf("ret = %d  str = %s\n", ret, &str[i]);
		if (str[i] == ' ')
		{
			while (str[i] == ' ')
				i++;
			--i;
		}
		else if (str[i] == '\"')
		{
			++ret;
			++i;
			while (str[i] != '\"' && str[i] != '\0')
			{
				if (str[i] == '\\')
					++i;
				++i;
			}
			if (str[i + 1] != ' ' && str[i + 1] != '\0')
				--ret;
		}
		else if (str[i] == '\'')
		{
			++ret;
			++i;
			while (str[i] != '\'' && str[i] != '\0')
			{	
				if (str[i] == '\\' && str[i + 1] != '\'')
					++i;
				++i;
			}
			if (str[i + 1] != ' ' && str[i + 1] != '\0')
				--ret;
		}
		else
		{
			++ret;
			while (str[i] != ' ' && str[i] != '\"' && str[i] != '\'' &&str[i] != '\0')
				++i;
			if (str[i] == '\"' || str[i] == '\'')
				--ret;
			--i;
		}
		i++;
	}
	return (ret);
}

int	count_words(const char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i] == ' ')
		++i;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\"')
		{
			++i;
			while (str[i] != '\"' && str[i] != '\0')
			{
				if (str[i] == '\\' && str[i + 1] == '\"')
					++i;
				++i;
				++ret;
			}
		}
		else if (str[i] == '\'')
		{
			++i;
			while (str[i] != '\'' && str[i] != '\0')
			{
				++i;
				++ret;
			}
		}
		else if (str[i] == '\\')
		{
			++i;
			++ret;
		}
		else
			++ret;
		++i;
	}
	return (ret);
}

char *fill_word(const char *str, t_env *enviro)
{
	int i;
	char *word;
	int dep;

	if (!(word = malloc(((count_words(str) + 1) * sizeof(char)))))
		return (NULL);
	ft_memset(word, 0, count_words(str) + 1);
	i = 0;
	dep = 0;
	while (str[i] == ' ')
		++i;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\"')
		{
			++i;
			while (str[i] != '\"' && str[i] != '\0')
			{
				if (str[i] == '\\' && str[i + 1] == '\"')
					++i;
				else if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' && str[i + 1] != '$' && str[i + 1] != '\\')
				{
					word = test1212(&dep, &i, word, str, *enviro);
					++i;
				}
				else
				{
					word[dep] = str[i];
					++dep;
					++i;
				}
			}
		}
		else if (str[i] == '\'')
		{
			++i;
			while (str[i] != '\'' && str[i] != '\0')
			{
				if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' && str[i + 1] != '$' && str[i + 1] != '\\')
				{
					word = test1212(&dep, &i, word, str, *enviro);
					++i;
				}
				else
				{
					word[dep] = str[i];
					++dep;
					++i;
				}
			}
		}
		else if (str[i] == '\\')
		{
			++i;
			word[dep] = str[i];
			++dep;
		}
		else
		{
			if (str[i] == '$' && str[i + 1] != ' ' && str[i + 1] != '\0' && str[i + 1] != '$' && str[i + 1] != '\\')
			{
				word = test1212(&dep, &i, word, str, *enviro);
			}
			else
			{
				word[dep] = str[i];
				++dep;
			}
		}
		++i;
	}
	word[dep] = '\0';
	return (word);
}

int advance(const char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ')
		++i;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '<' && str[i] != '>')
	{
		if (str[i] == '\"')
		{
			++i;
			while (str[i] != '\"' && str[i] != '\0')
			{
				if (str[i] == '\\' && str[i + 1] == '\"')
					++i;
				++i;
			}
		}
		else if (str[i] == '\'')
		{
			++i;
			while (str[i] != '\'' && str[i] != '\0')
				++i;
		}
		else if (str[i] == '\\')
			++i;
		++i;
	}
	return (i);
}

char		**ft_enhanced_split(char const *str, t_env *enviro)
{
	char	**tabl;
	int		i;
	int		j;

	i = 0;
	// printf("str init = %s\n", str);
	//printf("split nbr = %d\n", count_split(str));
	if (!(tabl = malloc((count_split(str) + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	j = 0;
	while (j < count_split(str))
	{
		// printf("count = %d\n", count_words(&str[i]));
	 	tabl[j] = fill_word(&str[i], enviro);
		j++;
		i = i + advance(&str[i]);
		//rajouter des trucs ici pour passer au prochain mots (sarreter au prochain espace pas dans des quotes)
	}
	tabl[j] = NULL;
	// i = 0;
	// while(tabl[i] != NULL)
	//   	printf("%s\n", tabl[i++]);
	// free_arr(tabl, j);

	return (tabl);
}
