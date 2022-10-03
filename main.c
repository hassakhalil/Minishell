/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/10/03 21:18:28 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int GLOBAL;


int complete_pipe(char *buff)
{
    int i = 0;
    int c = 0;
    int k = 0;

    while (buff[i])
    {
        if (!is_white_space(buff[i]))
        {
            c = buff[i];
            if (c == '|')
            {
                k++;
                if (k > 1)
                    return (1);
            }
            else if (k)
                k--;
        }
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
    sig  = 0;
    GLOBAL = 1;
	rl_replace_line("", 0);
	rl_on_new_line();
	write(1, "\n", 1);
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
            write(1, "exit\n", 5);
            exit (GLOBAL);
        }
        if (buff && *buff)
            add_history(buff);
        if (!empty_cmd(buff) || ft_exit(buff) || ft_cd(buff, env_list))
        {
            free(buff);
            continue;
        }
        //make fct builtin ->1/0
        //if (builtin)
        //    continue;
        //if (single builtin cmd)
        //{
            //tree = parsecmd(buff);
            //if (tree->type == EXEC)
            //cast
            //if cmd == exit
            //free
                //execute
            //else if cmd == cd
                //execute
                //clean
            //continue
        //}
        int pid = forkk();
        if (pid == 0)
        {
            signal(SIGQUIT,SIG_DFL);
	        signal(SIGINT, SIG_DFL);
            tree = parsecmd(buff);
            free(buff);
            executor(tree, env, envp,&flag_out, &flag_in);
            //parsing_tester(tree);
        }
        signal(SIGINT,SIG_IGN);
        wait(&exits);
        if ((WTERMSIG(exits) == 3 || WTERMSIG(exits) == 2) && GLOBAL != -1)
            GLOBAL = 128 + WTERMSIG(exits);
        else
            GLOBAL = WEXITSTATUS(exits);
        free(buff);
    }
    return(0);
}