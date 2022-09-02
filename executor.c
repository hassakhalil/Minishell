/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/30 17:13:17 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void errors(char *msg)
{
    write(2, msg, ft_strlen(msg));
    //clean everything
    exit(1);
}

int check_in_files(cmd *first_redir)
{
    t_redir   *tmp;
    int     i = 1;
    int     k;
    int     fd;

    tmp = (t_redir *)first_redir;
    while (tmp->cmd->type == REDIR)
    {
        tmp = (t_redir *)(tmp->cmd);
        if (tmp->fd != 0)
            break;     
        i++;
    }
    tmp = (t_redir *)first_redir;
    while (i)
    { 
        k = 1;
        while (k < i)
        {
            tmp = (t_redir *)(tmp->cmd);
            k++;
        }
        fd = open(tmp->file, tmp->mode);
        if (fd < 0)
        {
            close(fd);
            return (1);
        }
        close(fd);
        i--;
    }
    return (0);
}

void find_in_redir(cmd *tree, int *flag)
{
    t_pip *tree1;
    t_redir  *tree2;

    if (tree->type == PIPE)
    {
        tree1 = (t_pip *)tree;
        find_in_redir(tree1->left, flag);
        find_in_redir(tree1->right, flag);
    }
    else if (tree->type == REDIR)
    {
        tree2 = (t_redir *)tree;
        if (tree2->fd == 0 && check_in_files(tree))
            *flag = 2;
        find_in_redir(tree2->cmd, flag);
    }
}

void    executor(cmd *tree, env *env, int *flag)
{
    char    *s;
    int     p[2];
    int     id;
    int     i;
    int     open_fd;
    t_pip     *tree1;
    t_redir   *tree2;
    t_exec    *tree3;

   //signal(SIGHUP, handler);
    if (tree->type == PIPE)
    {
        tree1 = (t_pip *)tree;
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
        tree2 = (t_redir *)tree;
        if (*flag == 2 && tree2->fd == 1)
            errors("no such file or directory\n");
        open_fd = open(tree2->file, tree2->mode, 0666);
        if (open_fd < 0)
            exit (1);
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
        tree3 = (t_exec *)tree;
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