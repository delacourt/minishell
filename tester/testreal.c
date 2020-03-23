#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	printf("%d  %ld  %s\n", argc - 1, strlen(argv[1]), argv[1]);
	return (0);
}