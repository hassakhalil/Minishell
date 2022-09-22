/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/09/22 20:48:33 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int GLOBAL;

void	handler(int sig)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
    if  (sig == SIGINT)
	    rl_redisplay();
}

int main(int argc, char *argv[], char **env)
{
    static char     *buff = "";
    t_env           *envp;
    t_cmd           *tree;
    int             flag_in = 0;
    int             flag_out = 0;
    int             exits;

    //silencing warnings
    argv[argc] = 0;
    //
    printf("\e[1;1H\e[2J");
    envp = envpath();
    while (1)
    {
        signal(SIGQUIT,SIG_IGN);
	    signal(SIGINT, handler);
        buff = readline("$ ");
        if (!buff)
        {
            //clear everything
            exit (0);
        }
        if (buff && *buff)
            add_history(buff);
        if (!cd(buff))
            continue;
        if (!ft_strcmp(buff, "exit"))
        {
            //clear everything
            exit(0);
        }
        int pid = forkk();
        if (pid == 0)
        {
            signal(SIGQUIT,SIG_DFL);
	        signal(SIGINT, SIG_DFL);
            tree = parsecmd(buff);
            executor(tree, env, &flag_out, &flag_in);
            //parsing_tester(tree);
        }
        signal(SIGINT, SIG_IGN);
	    signal(SIGQUIT, handler);
        waitpid(pid, &exits, 0);
        GLOBAL = WEXITSTATUS(exits);
        //clear what you need to clear 
    }
    return(0);
}
