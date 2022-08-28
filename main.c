/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/08/28 14:49:49 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *getcmd()
{
    char *buff;

    if (isatty(fileno(stdin)))
        buff = readline("$ ");
    if (buff)
        return buff;
    return NULL;
}

int main(int ac, char **av, char **env)
{
    static char *buff;
    static char **var;
    struct env  *envp;
    cmd        *tree;
    int         flag = 0;

    system("clear");
    envp = envpath(env);
    while ((buff = getcmd()))
    {
        if (buff && *buff)
            add_history(buff);
        if (!cd(buff))
            continue;
        if (!strcmp(buff, "exit"))
            exit(0);
        if (forkk() == 0)
        {
            tree = parsecmd(buff);
            if (find_in_redir(tree) == 1)
            {
                printf("hello bitch\n");
                errors("No such file or directory\n");
                exit (1);
            }
            executor(tree, envp, &flag);
        }
        wait(0);
    }
    return(0);
}
