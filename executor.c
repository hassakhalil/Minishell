/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/20 18:33:22 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//SOME NOTES TO HEEEER
//how to execute struct *cmd
//ask elyas about exec struct

#define EXEC 1
#define REDIR 2
#define PIPE 3


void errors(char *msg)
{
    printf("%s\n", msg);
    //clean everything
    exit(1);
}

void    executor(cmd *result_tree, env *env)
{
    int p[2];
    int id;
    int open_fd;
    pip *tree1;
    redir *tree2;
    exec *tree3;

    if (result_tree->type == PIPE)
    {
        tree1 = (t_pipe *)result_tree;
        if (pipe(p) < 0)
            errors("pipe error");
        id = fork();
        if (id < 0)
            errors("fork error");
        if (id == 0)
        {
            close(p[0]);
            dup2(p[1], 1);
            close(p[1]);
            executor(tree1->left,env);
        }
        else
        {
            close(p[1]);
            dup2(p[0], 0);
            close(p[0]);
            executor(tree1->right,env);
            wait(0);
        }
    }
    else if (result_tree->type == REDIR)
    {
        tree2 = (t_redir *)result_tree;
        open_fd = open(tree2->file, tree2->mode);
        if (open_fd < 0)
            errors("open error");
        dup2(open_fd, tree2->fd);
        close(open_fd);
        executor(tree2->cmd, env, flag);
    }
    else
    {
        tree3 = (t_exec *)result_tree;
        char *p;
        int i = -1;
        while (env->path[++i])
        {
            p  = ft_strjoin(ft_strjoin(env->path[i], "/"), tree3->argv[0]);
            if (access(p, F_OK) != -1)
                execve(p, tree3->argv, env->path);
        }
    } 
}