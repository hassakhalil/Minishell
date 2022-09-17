/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/09/17 18:06:47 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handle(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
	rl_redisplay();
}

void	sig_handl(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "Quit: 3", 7);
	write(1, "\n", 1);
}

int exit_status;

int main(int argc, char *argv[], char **env)
{
    static char     *buff = "";
    t_env           *envp;
    t_cmd           *tree;
    int             flag_in = 0;
    int             flag_out = 0;
    int             exits = 0;

    //silencing warnings
    argv[argc] = 0;
    //
    system("clear");
    envp = envpath(env);

    while (1)
    {  
        signal(SIGQUIT,SIG_IGN);
	    signal(SIGINT, sig_handle);
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
            signal(SIGQUIT,SIG_DFL);
	        signal(SIGINT, SIG_DFL);
            tree = parsecmd(buff);
            executor(tree, envp, &flag_out, &flag_in);
            //parsing_tester(tree);
        }
        signal(SIGINT, SIG_IGN);
	    signal(SIGQUIT, sig_handl);
        waitpid(pid, &exits, 0);
        exit_status = WEXITSTATUS(exits);
        //printf("%d\n",exit_status);
    }
    return(0);
}
