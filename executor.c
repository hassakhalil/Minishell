/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/17 17:37:48 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void errors(char *name, char *msg)
{
    write(2,name, ft_strlen(name));
    write(2,":",1);
    write(2,msg, ft_strlen(msg));
    //clean everything
    exit(127);
}

int check_in_files(t_cmd *first_redir)
{
    t_redir   *tmp;
    int     i = 1;
    int     fd;

    tmp = (t_redir *)first_redir;
    while (tmp->type == REDIR && tmp->fd == 0)
    {
        fd = open(tmp->file, tmp->mode);
        if (fd < 0)
        {
            close(fd);
            return (1);
        }
        close(fd);
        tmp = (t_redir *)(tmp->cmd);  
        i++;
    }
    return (0);
}

void find_in_redir(t_cmd *tree, int *flag)
{
    t_pip *tree1;
    t_redir  *tree2;

    if (tree->type == REDIR)
    {
        tree2 = (t_redir *)tree;
        if (tree2->fd == 0 && check_in_files(tree))
        {
            *flag = 2;
            return ;
        }
        find_in_redir(tree2->cmd, flag);
    }
}

void    executor(t_cmd *tree, t_env *env, int *flag_out, int *flag_in)
{
    char    *s;
    int     p[2];
    int     id;
    int     i;
    int     exits = 0;
    int     open_fd;
    t_pip     *tree1;
    t_redir   *tree2;
    t_exec    *tree3;

    if (tree->type != PIPE)
    {
        find_in_redir(tree, flag_in);
        if (*flag_in == 2)
        {
            write(2, "No such file or directory\n", 27);
            exit(1);
        } 
    }

    if (tree->type == PIPE)
    {
        
        tree1 = (t_pip *)tree;
        if (pipe(p) < 0)
            printf("pipe error\n");
           // errors("pipe error\n");
        id = forkk();
        if (id == 0)
        {
            close(p[0]);
            dup2(p[1], 1);
            close(p[1]);
            executor(tree1->left, env, flag_out, flag_in);
        }
        id = forkk();
        if (id == 0)
        {
            close(p[1]);
            dup2(p[0], 0);
            close(p[0]);
            executor(tree1->right, env, flag_out, flag_in);
        }
        close(p[0]);
        close(p[1]);
        while(waitpid(id, &exits, 0) > 0);
        exit(WEXITSTATUS(exits));
    }
    else if (tree->type == REDIR)
    {
        tree2 = (t_redir *)tree;
        open_fd = open(tree2->file, tree2->mode, 0666);
        if (open_fd < 0)
            exit(1);
        if ((!(*flag_in) && !(tree2->fd)) || (!(*flag_out) && tree2->fd))
        {
            if (!(tree2->fd))
                *flag_in = 1;
            else
                *flag_out = 1;
            dup2(open_fd, tree2->fd);
        }
        close(open_fd);
        executor(tree2->cmd, env, flag_out, flag_in);
    }
    else
    {
        char *str;
        tree3 = (t_exec *)tree;
        i = -1;
        while (env->path[++i])
        { 
            s  = ft_strjoin(ft_strjoin(env->path[i], "/"), tree3->argv[0]);
            if (access(s, F_OK) != -1)
                str = s;
        }
        execve(str, tree3->argv, env->path);
        errors(tree3->argv[0],"command not found \n");
    }
}