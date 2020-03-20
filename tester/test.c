#include <stdio.h>
char		**ft_enhanced_split(char const *s);


int main(int argc, char **argv)
{
	int i;
	char **tab;

	tab = ft_enhanced_split(argv[1]);
	// i = 0;
	// while (tab[i] != NULL)
	// 	printf("%s\n", tab[i++]);
	return (0);
}
