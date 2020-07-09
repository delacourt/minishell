#include "../head/minishell.h"

int search_the_equal(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (i);
		else if (str[i] == ' ')
			return (-1);
		++i;
	}
	return (-1);
}

char **new_env_variable(char *str, char **envp)
{
	char **newenvp;
	int i;

	i = 0;
	newenvp = malloc((env_len(envp) + 2) * sizeof(char*));
	while (envp[i] != NULL)
	{
		newenvp[i] = malloc((ft_strlen(envp[i]) + 1) * sizeof(char));
		ft_strlcpy(newenvp[i], envp[i], ft_strlen(envp[i]) + 1);
		free(envp[i]);
		++i;
	}
	newenvp[i] = malloc((ft_strlen(str) + 1) * sizeof(char));
	ft_strlcpy(newenvp[i], str, ft_strlen(str) + 1);
	++i;
	newenvp[i] = NULL;
	free(envp);
	return (newenvp);
}

char **export_new(char **arg, t_env *enviro)
{
	int i;
	int j;
	int s;
	int found;

	i = 0;
	while (arg[i] != NULL)
	{
		s = search_the_equal(arg[i]);
		if (s == -1)
		{
			write(1, "mash: bad assignment\n", 21);
			enviro->lsc = 1;
			break;
		}
		j = 0;
		found = 0;
		while (enviro->envp[j] != NULL && found == 0) //la it trouve ?
		{
			if (ft_strncmp(arg[i], enviro->envp[j], s) == 0)
			{
				found = 1;
				free(enviro->envp[j]);
				enviro->envp[j] = malloc((ft_strlen(arg[i]) + 1) * sizeof(char));
				ft_strlcpy(enviro->envp[j], arg[i], ft_strlen(arg[i]) + 1);
			}
			++j;
		}
		if (found == 0) //la il la pas trouve
		{
			enviro->envp = new_env_variable(arg[i], enviro->envp);
		}
		//print_env(envp);
		++i;
	}
	return (enviro->envp);
}
