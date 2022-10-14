/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 00:30:01 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void check_in_files(t_cmd *redir)
{
    t_redir   *tmp;
    int     fd;

        tmp = (t_redir *)redir;
        fd = open(tmp->file, tmp->mode);
        if (fd < 0)
        { 
            close(fd);
            if (!access(tmp->file, F_OK))
                errors(tmp->file, 2);
            else
                errors(tmp->file, 3);
        }
        close(fd);
}

void find_in_redir(t_cmd *tree)
{
    t_redir  *tree2;

    if (tree->type == REDIR)
    {
        tree2 = (t_redir *)tree;
        find_in_redir(tree2->cmd);
        if (tree2->fd == 0)
           check_in_files(tree); 
    }
}

void    executor(t_cmd *tree, int *flag_out, int *flag_in, t_envvar **env_list)
{
    char    *s;
    int     i;
    int       open_fd;
    t_redir   *tree2;
    t_exec    *tree3;


    if (tree->type != PIPE)
        find_in_redir(tree);
    if (tree->type == PIPE)
        ft_pipe(tree, flag_out, flag_in, env_list);
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
        executor(tree2->cmd,flag_out, flag_in, env_list);
    }
    else
    {
        DIR *dir;
        char *str = NULL;
        tree3 = (t_exec *)tree;
        executor_builtin(tree3, env_list);
        dir = opendir(tree3->argv[0]);
        if (dir)
        {
            closedir(dir);
            errors(tree3->argv[0], 4);
        }
        if (ft_strchr(tree3->argv[0], '/'))
        {   
            if(access(tree3->argv[0], F_OK) != -1)
                str = ft_strdup(tree3->argv[0]);
            else
                errors(tree3->argv[0], 4);
        }
        else
        {
            i = -1;
            char    **path = envpath(*env_list);
            while (path && path[++i])
            {
                s  = ft_strjoin3(ft_strjoin(path[i], "/"), tree3->argv[0]);
                if (access(s, F_OK) != -1)
                    str = ft_strdup(s);
                free(s);
            }
            if (!str)
                   str = ft_strdup(tree3->argv[0]);
        }
        execve(str, tree3->argv, list_to_table(*env_list));
        free(str);
        errors(tree3->argv[0], 0);
    }
}