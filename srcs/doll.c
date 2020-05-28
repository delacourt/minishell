#include "../head/minishell.h"

int find_the_end_env(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\\' && str[i] != ' ' && str[i] != '$' && str[i] != '\'' && str[i] != '\"')
		++i;
	return (i);
}

char *test1212(int *dep, int *i, char *word, const char *str, char **envp)
{
	char *tmp;
	char *ret;
	int penv;
	int len = 0;

	len = find_the_end_env(&str[*i + 1]);
	//printf("%d\n", len);
	penv = 0;
	while (envp[penv] != NULL)
	{
		if (ft_strncmp(&str[*i + 1], envp[penv], len) == 0)
		{
			tmp = ft_strjoin(word, &envp[penv][len + 1]);
			ret = malloc((ft_strlen(tmp) + count_words(str) - search_the_equal(envp[penv])));
			ft_memset(ret, 0, (ft_strlen(tmp) + count_words(str) - search_the_equal(envp[penv])));
			ft_strlcpy(ret, tmp, ft_strlen(tmp) + 1);
			*i = *i + len;
			*dep = *dep + ft_strlen(&envp[penv][len + 1]);
			free(word);
			free(tmp);
			return(ret);
		}
		++penv;
	}
	*i = *i + len;
	return (word);
}
