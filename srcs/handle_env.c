#include "../head/minishell.h"

void free_env(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL)
	{
		free(envp[i]);
		++i;
	}
	//free(envp[i]);
	//free(envp);
}

int env_len(char **env)
{
	int i = 0;

	while (env[i] != NULL)
		++i;
	return (i);
}

char **new_env(char **envp)
{
	char **tenv;
	int i;

	tenv = malloc((env_len(envp) + 1) * sizeof(char*)); //proteger le malloc
	//printf("%d\n", env_len(envp));
	i = 0;
	while (envp[i] != NULL)
	{
		tenv[i] = malloc((ft_strlen(envp[i]) + 1) * sizeof(char));
		ft_strlcpy(tenv[i], envp[i], ft_strlen(envp[i]) + 1);
		++i;
	}
	tenv[i] = NULL;
	return (tenv);
}
