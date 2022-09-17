/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/09/17 17:38:18 by hkhalil          ###   ########.fr       */
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

int main(int ac, char **av, char **env)
{
    static char *buff = "";
    static char **var;
    t_env  *envp;
    t_cmd        *tree;
    int         flag_in = 0;
    int         flag_out = 0;
    int exits = 0;
    int status;

    system("clear");
    envp = envpath(env);
    signal(SIGQUIT,SIG_IGN);
	signal(SIGINT, handler);
    while (1)
    {
        buff = readline("$ ");
        if (!buff)
            exit (0);
        if (buff && *buff)
            add_history(buff);
        if (!cd(buff))
            continue;
        if (!strcmp(buff, "exit"))
            exit(0);
        int pid = forkk();
        if (pid == 0)
        {
            tree = parsecmd(buff);
            //find_in_redir(tree, &flag_in);
            executor(tree, envp, &flag_out, &flag_in);
            //parsing_tester(tree);
        }
        waitpid(pid, &exits, 0);
        int exit_status = WEXITSTATUS(exits);
        //printf("%d\n",exit_status);
    }
    return(0);
}
