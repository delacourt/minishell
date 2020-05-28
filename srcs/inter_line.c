#include "../head/minishell.h"

void fill(t_key *key)
{
	key->g[0] = 27;
	key->g[1] = 91;
	key->g[2] = 68;
	key->g[3] = 0;
	key->d[0] = 27;
	key->d[1] = 91;
	key->d[2] = 67;
	key->d[3] = 0;
	key->h[0] = 27;
	key->h[1] = 91;
	key->h[2] = 65;
	key->h[3] = 0;
	key->b[0] = 27;
	key->b[1] = 91;
	key->b[2] = 66;
	key->b[3] = 0;
}

void put_in_histo(t_env *enviro, char *tst)
{
	char *tmp;
	char *tmp2;
	int i;

	enviro->histo[0] = tst;
	tmp = enviro->histo[1];
	enviro->histo[1] = enviro->histo[0];
	tmp2 = enviro->histo[2];
	enviro->histo[2] = tmp;
	tmp = enviro->histo[3];
	enviro->histo[3] = tmp2;
	tmp2 = enviro->histo[4];
	enviro->histo[4] = tmp;
	tmp = enviro->histo[5];
	enviro->histo[5] = tmp2;
	tmp2 = enviro->histo[6];
	enviro->histo[6] = tmp;
	tmp = enviro->histo[7];
	enviro->histo[7] = tmp2;
	tmp2 = enviro->histo[8];
	enviro->histo[8] = tmp;
	tmp = enviro->histo[9];
	enviro->histo[9] = tmp2;
	tmp2 = enviro->histo[10];
	enviro->histo[10] = tmp;
	
	free(enviro->histo[10]);
	free(tmp2);
	enviro->histo[10] = NULL;
}

void test1213(char *tst, int len, char c)
{
	char *tmp;

	tmp = ft_strdup(&tst[len]);

	//printf("%s\n", tmp);
	tst[len] = c;
	ft_strlcpy(&tst[len + 1], tmp, ft_strlen(tmp) + 1);
	free(tmp);	
}

int inter_line(char **line, t_env *enviro)
{
	char t;
	char *tst;
	char *tmp;
	char *hold;
	int ou = 1;
	int k;
	t_key key;
	int end = 0;

	fill(&key);

	//ft_memset(tst, 0, 1024);
	tst = ft_calloc(2, sizeof(char));
	while (1)
	{
		t = 0;
		read(0, &t, 1);
		//printf("%d\n", t);
		if((t >= 32 && t <= 126) || t == 27)
		{
			hold = ft_strdup(tst);
			tmp = tst;
			tst = ft_calloc(ft_strlen(hold) + 2, sizeof(char));
			free(tmp);
			ft_strlcpy(tst, hold, ft_strlen(hold) + 1);
			test1213(tst, end, t);
			++end;
		
			free(hold);
		}
		for (int i = 0; tst[i] != '\0'; ++i)
			;//printf("%d\n", tst[i]);
		if (t == '\n')
		{
			put_in_histo(enviro, tst);
			*line = tst;
			return (1);
		}
		else if (t == 4 && ft_strlen(tst) == 0) //ctrl D
			exit(0);
		else if (t == 3) //ctrl C
			;
		else if (t == 28) //ctrl backslash
			;
		else if (ft_strnstr(tst, key.g, ft_strlen(tst)))
		{
			//printf("yo\n");
			//printf("end = %d\nlen = %zu", end, ft_strlen(tst));
			if (end - 3 > 0)
			{
				write(1, &key.g, 3);
				--end;
				ft_strlcpy(&tst[end - 2], &tst[end + 1], 1024);
			}
			else
			{
				//printf("%d\n", end);
				ft_strlcpy(tst, &tst[end], 1024);
			}
			end = end - 3;
		}
		else if (ft_strnstr(tst, key.d, ft_strlen(tst)))
		{
			//printf("end = %d\nlen = %zu", end, ft_strlen(tst));
			if (end < ft_strlen(tst))
			{
				write(1, &key.d, 3);
				++end;
				ft_strlcpy(&tst[end - 4], &tst[end- 1], 1024);
			}
			else
			{
				ft_strlcpy(&tst[end - 3], &tst[end], 1024);
			}
			//printf("%d\n", tst[end - 1]);
			end = end - 3;
		}
		else if (ft_strnstr(tst, key.h, ft_strlen(tst)))
		{
			if (enviro->histo[ou] != NULL)
			{
				++ou;
				for (k = 0; k < ft_strlen(tst) - ft_strlen(&tst[end]) - 3; ++k)
					write(1, &key.g, 3);
				for (k = 0; k < ft_strlen(tst) - 3; ++k)
					write(1, " ", 1);
				for (k = 0; k < ft_strlen(tst) - 3; ++k)
					write(1, &key.g, 3);
				free(tst);
				tst = ft_strdup(enviro->histo[ou - 1]);
				write(1, tst, ft_strlen(tst));
				end = ft_strlen(tst);
			}
			else
			{//printf("haut\n");
				ft_strlcpy(&tst[end - 3], &tst[end], 1024);
				end = end - 3;
			}
		}
		else if (ft_strnstr(tst, key.b, ft_strlen(tst)))
		{
			if (ou > 2)
			{
				--ou;
				for (k = 0; k < ft_strlen(tst) - ft_strlen(&tst[end]) - 3; ++k)
					write(1, &key.g, 3);
				for (k = 0; k < ft_strlen(tst) - 3; ++k)
					write(1, " ", 1);
				for (k = 0; k < ft_strlen(tst) - 3; ++k)
					write(1, &key.g, 3);
				free(tst);
				tst = ft_strdup(enviro->histo[ou - 1]);
				write(1, tst, ft_strlen(tst));
				end = ft_strlen(tst);
			}
			else if (ou <= 2)
			{
				if (ou == 2)
					--ou;
				for (k = 0; k < ft_strlen(tst) - ft_strlen(&tst[end]) - 3; ++k)
					write(1, &key.g, 3);
				for (k = 0; k < ft_strlen(tst) - 3; ++k)
					write(1, " ", 1);
				for (k = 0; k < ft_strlen(tst) - 3; ++k)
					write(1, &key.g, 3);
				free(tst);
				tst = ft_strdup("");
				end = 0;
			}
			else
			{//printf("haut\n");
				ft_strlcpy(&tst[end - 3], &tst[end], 1024);
				end = end - 3;
			}
		}
		else if (t == 127 && end > 0)
		{
			ft_strlcpy(&tst[end - 1], &tst[end], 1024);
			end = end - 1;
			write(1, &key.g, 3);
			write(1, &tst[end], ft_strlen(&tst[end]));
			write(1, " ", 1);
			for (int j = 0; j <= ft_strlen(&tst[end]); ++j)
				write(1, &key.g, 3);
		}
		else if (!(ft_strchr(tst, 27)) && (t >= 32 && t <= 126))
		{
			write(1, &t, 1);
			write(1, &tst[end], ft_strlen(&tst[end]));
			for (int i = 0; i < ft_strlen(&tst[end]); ++i)
				write(1, &key.g, 3);
			//++end;
			//printf("%d\n", end);
		}
		//printf("%d\n", t);
	}
}
