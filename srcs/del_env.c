#include "../head/minishell.h"

char **del_env_variable(int len, char **envp)
{
	char **newenvp;
	int i;
	int j;

	newenvp = malloc((len + 1) *sizeof(char*));
	i = 0;
	j = 0;
	while (i < len)
	{
		if (envp[i] != NULL)
		{
			newenvp[j] = malloc((ft_strlen(envp[i]) + 1) * sizeof(char));
			ft_strlcpy(newenvp[j], envp[i], ft_strlen(envp[i]) + 1);
			++j;
		}
		++i;
	}
	newenvp[j] = NULL;
	free_env(envp);
	return(newenvp);
}

char **unset_new(char **arg, t_env *enviro)
{
	int i;
	int j;
	int len;

	i = 0;	
	while (arg[i] != NULL)
	{
		j = 0;
		len = env_len(enviro->envp);
		while (enviro->envp[j] != NULL)
		{
			if (ft_strncmp(arg[i], enviro->envp[j], ft_strlen(arg[i])) == 0)
			{
				free(enviro->envp[j]);
				enviro->envp[j] = NULL;
			}
			++j;
		}
		if (len != env_len(enviro->envp))
			enviro->envp = del_env_variable(len, enviro->envp);
		++i;
	}
	return (enviro->envp);
}