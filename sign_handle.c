#include "minishell.h"

void sighandler(int signum)
{
	write(1, "\n", 1);
	print_new_line();
}