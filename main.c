/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/09/25 12:01:54 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int GLOBAL;

void    child_handler(int sig)
{
    dprintf(2, "[[ paased from child_handler ]]\n");
    sig = 0;
    GLOBAL = 130;
    //exit(130);
}

int complete_pipe(char *buff)
{
    int i = 0;
    int c = 0;

    while (buff[i])
    {
        if (!is_white_space(buff[i]))
            c = buff[i];
        i++;
    }
    if (c == '|')
        return (1);
    return (0);
}

int empty_cmd(char *buff)
{
    int i = 0;

    while (buff[i])
    {
        if (!is_white_space(buff[i]))
            return (1);
        i++;
    }
    return (0);
}

void	handler(int sig)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
    if  (sig == SIGINT)
	    rl_redisplay();
    dprintf(2, "{{ passed from the handler function }}\n");
}

int main(int argc, char *argv[], char **env)
{
    static char     *buff = "";
    char            *tmp;
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
        //test signals
        //signal(SIGQUIT, handler);
        //end test
        buff = readline("$ ");
        if (!buff)
        {
            //clear everything
            exit (GLOBAL);
        }
        if (buff && *buff)
        {
            //signal(SIGQUIT, SIG_DFL);
            if (complete_pipe(buff))
            {
                tmp = readline("> ");
                while (!empty_cmd(tmp))
                    tmp = readline("> ");
                buff = ft_strjoin(buff, tmp);
            }
            add_history(buff);
        }
        if (!cd(buff) || !empty_cmd(buff))
            continue;
        if (!ft_strcmp(buff, "exit"))
        {
            //clear everything
            exit(0);
        }
        int pid = forkk();
        if (pid == 0)
        {
            
            tree = parsecmd(buff);
            signal(SIGQUIT,SIG_DFL);
	        signal(SIGINT, SIG_DFL);
            executor(tree, env, envp,&flag_out, &flag_in);
            
            //parsing_tester(tree);
        }
        signal(SIGINT, child_handler);
        dprintf(2, "[ global  = %d\n ]", GLOBAL);
	    //signal(SIGQUIT, SIG_DFL);
        waitpid(pid, &exits, 0);
        GLOBAL = WEXITSTATUS(exits);
        //signal(SIGINT, child_handler);
        //signal(SIGINT, SIG_IGN);
       
        //clear what you need to clear 
    }
    return(0);
}