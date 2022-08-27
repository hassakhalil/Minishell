/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/27 22:34:40 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void errors(char *msg)
{
    write(2, msg, ft_strlen(msg));
    //clean everything
    exit(1);
}

//find_in_redir(); heeeere

int check_in_files(cmd **first_redir)
{
    redir   *tmp;
    char    **table;
    int     i = 1;
    int     k;
    int     fd;

    if (!first_redir)
       return (0);
    tmp = (redir *)(*first_redir);
    while (tmp->cmd->type == REDIR)
    {
        tmp = (redir *)(tmp->cmd);
        if (tmp->fd != 0)
            break;     
        i++;
    }
    tmp = (redir *)(*first_redir);
    while (i)
    {
        k = 0;
        while (k < i)
        {
            tmp = (redir *)(tmp->cmd);
            k++;
        }
        if (open(tmp->file, tmp->mode) < 0)
            return (1);
        i--;
    }
    return (0);
}

void    executor(cmd *tree, env *env, int *flag)
{
    char    *s;
    int     p[2];
    int     id;
    int     i;
    int     open_fd;
    pip     *tree1;
    redir   *tree2;
    exec    *tree3;

    if (tree->type == PIPE)
    {
        tree1 = (pip *)tree;
        if (pipe(p) < 0)
            errors("pipe error\n");
        id = forkk();
        if (id == 0)
        {
            close(p[0]);
            dup2(p[1], 1);
            close(p[1]);
            executor(tree1->left, env, flag);
        }
        else
        {
            close(p[1]);
            dup2(p[0], 0);
            close(p[0]);
            executor(tree1->right, env, flag);
            wait(0);
        }
    }
    else if (tree->type == REDIR)
    {
        tree2 = (redir *)tree;
        open_fd = open(tree2->file, tree2->mode, 0666);
        if (!(*flag))
        {
            *flag = 1; 
            dup2(open_fd, tree2->fd);
        }
        close(open_fd);
        executor(tree2->cmd, env, flag);
    }
    else
    {
        tree3 = (exec *)tree;
        i = -1;
        while (env->path[++i])
        {
            s  = ft_strjoin(ft_strjoin(env->path[i], "/"), tree3->argv[0]);
            if (access(s, F_OK) != -1)
            {
                execve(s, tree3->argv, env->path);
                errors("execve error\n");
            }
        }
    } 
}