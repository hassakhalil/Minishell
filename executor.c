/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/29 04:59:30 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int errno ;

void errors(char *name, int flag)
{
    if (flag == 2 || flag == 3)
    {
        write(2,name, ft_strlen(name));
        if (flag == 2)
            write(2, ": Permission denied\n", 21);
        else
             write(2, ": No such file or directory\n", 29);
        exit(1);
    }
    if (errno == 2 || errno == 13)
    {
        if (ft_strchr(name, '/'))
            perror(name);
        else
        {
            write(2,name, ft_strlen(name));
            write(2, ": command not found\n",21);
        }
        if (errno == 2)
            exit(127);
        else if (errno == 13)
            exit(126);
    } 
}
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

void    executor(t_cmd *tree, char **env, t_env *envp,int *flag_out, int *flag_in)
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
        find_in_redir(tree);
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
            executor(tree1->left, env, envp,flag_out, flag_in);
        }
        id = forkk();
        if (id == 0)
        {
            close(p[1]);
            dup2(p[0], 0);
            close(p[0]);
            executor(tree1->right, env, envp,flag_out, flag_in);
        }
        close(p[0]);
        close(p[1]); 
        waitpid(id, &exits, 0);
        while(wait(0) > 0);
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
        executor(tree2->cmd, env, envp,flag_out, flag_in);
    }
    else
    {
        char *str = NULL;
        tree3 = (t_exec *)tree;   
        if (ft_strchr(tree3->argv[0], '/') && access(tree3->argv[0], F_OK) != -1)
            str = ft_strdup(tree3->argv[0]);
        else
        {
            i = -1;
            while (envp && envp->path[++i])
            {
                s  = ft_strjoin(ft_strjoin(envp->path[i], "/"), tree3->argv[0]);
                if (access(s, F_OK) != -1)
                    str = ft_strdup(s);
            }
            if (!str)
                   str = ft_strdup(tree3->argv[0]);  
        }
        execve(str, tree3->argv, env);
        errors(tree3->argv[0], 0);
    }
}