/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: delacourt <delacourt@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 15:09:19 by delacourt         #+#    #+#             */
/*   Updated: 2020/03/13 17:26:18 by delacourt        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <libc.h>

int main(void)
{
    int i;
    char *line;
    pid_t pid;

    write(1, "&> ", 3);
    while (1)
    {
        i = get_next_line(0, &line);
        pid = fork();
        if (pid == 0)
            execve(line, NULL, NULL);
        else
            wait(&pid);
        if (i == 0)
            return (0);
        write(1, "&> ", 3);
    }
    return (0);
}
