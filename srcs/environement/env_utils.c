#include "../../head/minishell.h"

char **get_env_variable(char **envp, char *str)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(str);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(str, envp[i], len) == 0)
			return (&envp[i]);
		++i;
	}
	return (NULL);
}