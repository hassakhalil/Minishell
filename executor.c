/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/23 19:36:06 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//SOME NOTES TO HEEEER
//fix multiple out redir + in redir
//fix compatibility problem

#define EXEC 1
#define REDIR 2
#define PIPE 3


void errors(char *msg)
{
    write(2, msg, ft_strlen(msg));
    //clean everything
    exit(1);
}

void    executor(cmd *result_tree, env *env)
{
    char    *s;
    int     p[2];
    int     id;
    int     i;
    int     open_fd;
    pip     *tree1;
    redir   *tree2;
    exec    *tree3;

    if (result_tree->type == '|')
    {
        tree1 = (pip *)result_tree;
        if (pipe(p) < 0)
            errors("pipe error\n");
        id = fork();
        if (id < 0)
            errors("fork error\n");
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
    else if (result_tree->type == '>' || result_tree->type == '<')
    {
        tree2 = (redir *)result_tree;
        open_fd = open(tree2->file, tree2->mode , 0666);
        if (open_fd < 0)
            errors("open error\n");
        dup2(open_fd, tree2->fd);
        close(open_fd);
        executor(tree2->cmd, env);
    }
    else
    {
        tree3 = (exec *)result_tree;
        i = -1;
        while (env->path[++i])
        {
            s  = ft_strjoin(ft_strjoin(env->path[i], "/"), tree3->argv[0]);
            if (access(s, F_OK) != -1)
            {
                execve(s, tree3->argv, env->path);
                write(2, "execve error\n", 14);
            }
        }
    } 
}