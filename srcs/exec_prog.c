#include "../head/minishell.h"

int exec_prog(char *line, char **argv, char **envp, t_r_output redir, t_pipe *pip)
{
	pid_t pid;

	pid = fork();
    if (pid == 0)
	{
		if (pip->total > 1 && pip->nbr != 0)
		{
			dup2(pip->pipefd[pip->nbr - 1][0], 0);
		}
		if (pip->total > 1 && pip->nbr + 1 < pip->total)
		{
			dup2(pip->pipefd[pip->nbr][1], 1);
		}
		if (redir.out != 1)
    		dup2(redir.out, 1);
		if (redir.in != 0)
			dup2(redir.in, 0);
		execve(line, argv, envp);
	}
	else
	{
		wait(&pid);
		if (pip->total > 1 && pip->nbr + 1 < pip->total)
			close(pip->pipefd[pip->nbr][1]);
	}
	++pip->nbr;
	return (pid);
}

int search_and_exec(char **tabl, char **envp, int *lsc, t_r_output redir, t_pipe *pip)
{
	struct stat statbuff;
	char *path = NULL;
	char **pathed;
	int i;
	int j;
	int k;
	char *try;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			path = &envp[i][5];
		++i;
	}
	if (path == NULL)
	{
		path = malloc(1 * sizeof(char));
		path[0] = '\0';
	}
	if (ft_strchr(tabl[0], '/')) //check si cest un path absolu ou relatif ou si lon doit utiliser le path
	{
		if (stat(tabl[0], &statbuff) == 0) //est ce que le fichier / dossier existe
		{
			// if (S_ISDIR(statbuff.st_mode) == 1) //check si cest un directory // feature naze
			// 	cd(tabl, lsc);
			if (S_ISDIR(statbuff.st_mode) == 0) //ou un file
				*lsc = exec_prog(tabl[0], tabl, envp, redir, pip);
		}
		else
		{
			*lsc = 1;
			write(1, "mash: no such file or directory: ", ft_strlen("mash: no such file or directory: "));
			write(1, tabl[0], ft_strlen(tabl[0]));
			write(1, "\n", 1);
		}
	}
	else //est ce que l'executablle est dans le path
	{
		pathed = ft_split(path, ':'); //parse le path en splitant a chaque : (echo $PATH)
		i = 0;
		while(pathed[i] != NULL)
		{
			//try = ft_strjoin(tabl[0], pathed[i]);
			try = malloc(ft_strlen(tabl[0]) + ft_strlen(pathed[i]) + 2);
			j = 0;
			k = 0;
			while (pathed[i][j] != '\0')
			{
				try[k] = pathed[i][j];
				++k;
				++j;
			}																		//remplacer par un strjoin avec un /
			try[k] = '/';
			++k;
			j = 0;
			while (tabl[0][j] != '\0')
			{
				try[k] = tabl[0][j];
				++k;
				++j;
			}
			try[k] = '\0';
			++i;
			//malloc et ctrlc ctrlv mon path + mon executablle
			//printf("%s\n", try);

			if (stat(try, &statbuff) == 0) //check si ce dernier existe
			{
				// printf("%s\n", try);
				// print_env(tabl, 1, lsc);
				//write(pip->pipefd[0][0], "wesh la\nyo testreen", 19);
				//printf("%d\n", pip->nbr);
				*lsc = exec_prog(try, tabl, envp, redir, pip); //virer le null et remplacer par lenv
				free(try);
				free_env(pathed);
				return (0);
			}
			else if (pathed[i] == NULL)	//rentre la dedans si jai test tous les path sans trouver lexcecutablle
			{
				*lsc = 1;
				write(1, "mash: command not found: ", ft_strlen("mash: command not found: "));
				write(1, tabl[0], ft_strlen(tabl[0]));
				write(1, "\n", 1);
				free(try);
				free_env(pathed);
				return (1);
			}
			free(try);
		}
		*lsc = 1;
		free_env(pathed);
		write(1, "mash: no such file or directory: ", ft_strlen("mash: no such file or directory: "));
		write(1, tabl[0], ft_strlen(tabl[0]));
		write(1, "\n", 1);
	}
	return (1);	
}
