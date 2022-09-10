/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/09/10 22:35:00 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handler(int sig)
{
    if (sig == SIGHUP)
    {

        write(2, "passed from here 1\n", 20);
        exit(0);
    }
    else if (sig == SIGINT)
    {
        write(1, "\n" ,1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

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
    static char *buff = "";
    static char **var;
    struct env  *envp;
    cmd        *tree;
    int         flag_in = 0;
    int         flag_out = 0;

    system("clear");
    envp = envpath(env);
    signal(SIGQUIT,SIG_IGN);
	signal(SIGINT, handler);
    while (buff)
    {
        buff = getcmd();
        if (!buff)
            exit (0);
        if (buff && *buff)
            add_history(buff);
        if (!cd(buff))
            continue;
        if (!strcmp(buff, "exit"))
            exit(0);
        if (forkk() == 0)
        {
            tree = parsecmd(buff);
            find_in_redir(tree, &flag_in);
            if (flag_in == 2)
                errors("no such file or directory\n");
            executor(tree, envp, &flag_out, &flag_in);
            //parsing_tester(tree);
        }
        wait(0);
    }
    return(0);
}
