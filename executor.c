/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/09 23:58:59 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void errors(char *msg)
{
    printf("%s\n", msg);
    //clean everything
    exit(1);
}

void    executor(void *tree)
{
    int fd[2];
    int

    if (/*treetype == pipe*/)
    {
        if (pipe(fd) < 0)
            errors("pipe error");

        if (fork() == 0)
        {
            close(1);
            dup(fd[1]);
            close(fd[0]);
            close(fd[1]);
            //if redirection 
            //redirect
            execve();
        }
        wait();
        if (/*pipe->left == pipe*/)
            //executor recursive call
        if (fork() == 0)
        {
            close(0);
            dup(fd[0]);
            close(fd[0]);
            close(fd[1]);
            if (/*redirection*/)
                //redirect
            execve();
        }
        close(fd[0]);
        close(fd[1]);
        wait();
    }
    else
        //search for redirections
        //exec cmd
        
}