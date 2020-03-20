#include "minishell.h"

static void	*free_arr(char **tab, int j)
{
	while (j >= 0)
	{
		free(tab[j]);
		j--;
	}
	free(tab);
	return (NULL);
}

static int	count_split(const char *str)
{
	int i;
	int ret;
	int oldret;

	i = 0;
	ret = 1;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
		{
			++ret;
			while (str[i] == ' ')
				i++;
			--i;
		}
		else if (str[i] == '\"')
		{
			oldret = ret;
			if (str[i + 1] == '\"')
				--ret;
			++ret;
			++i;
			while (str[i] != '\"' && str[i] != '\0')
			{
				if (str[i] == '\\')
					++i;
				++i;
			}
			if (str[i + 1] != ' ' && oldret != ret)
				--ret;
		}
		else if (str[i] == '\'')
		{
			oldret = ret;
			if (str[i + 1] == '\"')
				--ret;
			++ret;
			++i;
			while (str[i] != '\'' && str[i] != '\0')
			{	
				if (str[i] == '\\' && str[i + 1] != '\'')
					++i;
				++i;
			}
			if (str[i + 1] != ' ' && oldret != ret)
				--ret;
		}
		else if (str[i] == '\\')
			++i;
		i++;
	}
	if (i > 0 && str[i - 1] == ' ')
		ret--;
	return (ret);
}

static int	count_words(const char *str)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (str[i] != '\0' && str[i] != ' ')
	{
		while (str[i] == ' ')
			++i;
		if (str[i] == '\"')
		{
			++i;
			while (str[i] != '\"' && str[i] != '\0')
			{
				if (str[i] == '\\')
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
				if (str[i] == '\\' && str[i + 1] != '\'')
					++i;
				++i;
				++ret;
			}
		}
		else if (str[i] == '\\')
			++i;
		else
		{
			++i;
			++ret;
		}
	}
	return (ret);
}

char *fill_word(char *str)
{
	char *mal; // a malloc en callant count words et return

	//checker si oui ou non il faut le charactere en question, 
}

char		**ft_enhanced_split(char const *str)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	i = 0;

	if (!(tab = malloc((count_split(str) + 1) * sizeof(char*))))
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] == ' ')
		i++;
	while (j < count_split(str))
	{
		k = 0;
		tab[j] = fill_word(&str[i]);
		tab[j][k] = '\0';
		j++;
		//rajouter des trucs ici pour passer au prochain mots (sarreter au prochain espace pas dans des quotes)
	}
	tab[j] = NULL;
	return (tab);
}
