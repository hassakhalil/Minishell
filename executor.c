/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/27 19:13:43 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int errno ;

void errors(char *name, int flag)
{
    if (flag == 2 || flag == 3)
    {
        if (flag == 2)
            write(2, "Permission denied\n", 19);
        else
             write(2, "No such file or directory\n", 27);
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
int check_in_files(t_cmd *first_redir)
{
    t_redir   *tmp;
    int     i = 1;
    int     fd;

    tmp = (t_redir *)first_redir;
    while (tmp->type == REDIR && tmp->fd == 0)
    {
        fd = open(tmp->file, tmp->mode);
        if (fd <0)
        { 
            close(fd);
            if (!access(tmp->file, F_OK))
                return (2);
            else
                return (3);
        }
        close(fd);
        tmp = (t_redir *)(tmp->cmd);  
        i++;
    }
    return (0);
}

void find_in_redir(t_cmd *tree, int *flag)
{
    t_redir  *tree2;

    if (tree->type == REDIR)
    {
        tree2 = (t_redir *)tree;
        if (tree2->fd == 0 && check_in_files(tree))
        {
            *flag = check_in_files(tree);
            return ;
        }
        find_in_redir(tree2->cmd, flag);
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


    //signal(SIGINT, child_handler);
    if (tree->type != PIPE)
    {
        find_in_redir(tree, flag_in);
        if (*flag_in == 2 || *flag_in == 3)
            errors(NULL, *flag_in);
    }
    // signal(SIGINT, child_handler);
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
        while(waitpid(-1, &exits, 0) > 0);
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