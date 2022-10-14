/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/14 20:27:44 by hkhalil          ###   ########.fr       */
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
    int     p[2];
    int     id;
    int     i;
    int     last;
    int     mid;
    int       open_fd;
    t_pip     *tree1;
    t_redir   *tree2;
    t_exec    *tree3;


    if (tree->type != PIPE)
        find_in_redir(tree);
    if (tree->type == PIPE)
    {
        tree1 = (t_pip *)tree;
        if (pipe(p) < 0)
            perror("pipe error");
        id = forkk();
        if (id == 0)
        {
            close(p[0]);
            dup2(p[1], 1);
            close(p[1]);
            executor(tree1->left, flag_out, flag_in, env_list);
        }
        id = forkk();
        if (id == 0)
        {
            close(p[1]);
            dup2(p[0], 0);
            close(p[0]);
            executor(tree1->right, flag_out, flag_in, env_list);
        }
        close(p[0]);
        close(p[1]);
        waitpid(id, &last , 0);
        while(wait(&mid) > 0)
        {
            if ((WTERMSIG(mid) == 3 || WTERMSIG(mid) == 2) && (WTERMSIG(last) != 3 && WTERMSIG(last) != 2))
            GLOBAL = -1;
        }
        exit(WEXITSTATUS(last));
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
        executor(tree2->cmd,flag_out, flag_in, env_list);
    }
    else
    {
        DIR *dir;
        char *str = NULL;
        tree3 = (t_exec *)tree;
         //debug
        dprintf(2, "argv[0] = { %s }\n", tree3->argv[0]);
        //end debug
        executor_builtin(tree3, env_list);
        //debug
        dprintf(2, "after builtin\n");
        //end debug
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