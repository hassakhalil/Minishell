/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/11 19:14:49 by hkhalil          ###   ########.fr       */
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
    int p[2];
    int id1;
    int id2;

    //cast tree to cmd to access tree->type
    if (tree->type == PIPE)
    {
        if (pipe(p) < 0)
            errors("pipe error");
        id1 = fork();
        if (id1 < 0)
            errors("fork error");
        if (id1 == 0)
        {
            close(1);
            dup(p[1]);
            close(p[0]);
            close(p[1]);
            if (tree->left == REDIR) 
                //redirect
            execve();
            errors("execve error");
        }
        else if (tree->right->type == PIPE)
        {
            close(0);
            dup(p[0]);
            close(p[0]);
            executor(tree->right);
        }
        if (id1 != 0)
        {
            id2 = fork();
            if (id2 < 0)
                errors("fork error");
            if (id2 == 0)
            {
                close(0);
                dup(p[0]);
                close(p[0]);
                close(p[1]);
                if (tree->right->type == REDIR)
                    //redirect
                execve();
                errors("execve error");
            }
        }
        else
        {
            close(p[0]);
            close(p[1]);
            wait();
        }
     }
    else
    {
        if (tree->type == REDIR)
            //do redir
        execve();
        errors("execve error");
    }
        
}