#include "../head/minishell.h"

static size_t		ft_itoa_len(int n)
{
	size_t	r;

	if (n == 0)
		return (1);
	r = 0;
	if (n < 0)
		r++;
	while (n)
	{
		n /= 10;
		r++;
	}
	return (r);
}

char				*ft_itoa(int n)
{
	size_t	l;
	size_t	e;
	char	*r;

	l = ft_itoa_len(n);
	if (!(r = (char *)malloc(l + 1)))
		return (NULL);
	r[l] = '\0';
	if (n < 0)
	{
		r[0] = '-';
		e = 1;
	}
	else
		e = 0;
	while (l-- > e)
	{
		r[l] = '0' + n % 10 * (n < 0 ? -1 : 1);
		n /= 10;
	}
	return (r);
}

int find_the_end_env(const char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\\' && str[i] != ' ' && str[i] != '$' && str[i] != '\'' && str[i] != '\"')
		++i;
	return (i);
}

char *test1212(int *dep, int *i, char *word, const char *str, t_env enviro)
{
	char *tmp;
	char *ret;
	char *tmp2;
	int penv;
	int len = 0;
	int lentest = 0; //$W prblm
	char **envp;

	envp = enviro.envp;
	//len = find_the_end_env(&str[*i + 1]);
	//printf("%d\n", len);
	penv = 0;
	if (ft_strncmp(&str[*i], "$?", 2) == 0)
	{
		tmp2 = ft_itoa(enviro.lsc);
		tmp = ft_strjoin(word, tmp2);
		ret = malloc((ft_strlen(tmp) + count_words(str) - 1));
		ft_memset(ret, 0, (ft_strlen(tmp) + count_words(str) - 1));
		ft_strlcpy(ret, tmp, ft_strlen(tmp) + 1);
		*i = *i + 1;
		*dep = *dep + ft_strlen(tmp2);
		free(word);
		free(tmp);
		free(tmp2);
		return(ret);
	}
	while (envp[penv] != NULL)
	{
		len = search_the_equal(envp[penv]);
		lentest = find_the_end_env(&str[*i + 1]);
		if (len < lentest)
			len = lentest;
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
