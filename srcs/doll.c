#include "../head/minishell.h"

int n_len(int nbr)
{
	int ct;
    unsigned int t_nb;

    ct = 1;
    t_nb = nbr;
    if (nbr < 0)
    {
        ct = 2;
        t_nb = t_nb * -1;
    }
    while (t_nb >= 10)
    {
        ++ct;
        t_nb = t_nb / 10;
    }
    return (ct);
}

int		i_len(long nb)
{
	int		len;

	len = 0;
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char *str;
	long	n;
	int		i;

	n = nb;
	i = i_len(n);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i--] = '\0';
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n = n / 10;
		i--;
	}
	return (str);
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
