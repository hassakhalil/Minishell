/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 14:51:47 by iakry             #+#    #+#             */
/*   Updated: 2022/08/17 19:55:41 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printheader()
{
    printf("\033[1;31m");
    printf("\n __    __     __     __   __     __     ______     __  __     ______     __         __        \n");
    printf("/\\  -./  \\   /\\ \\   /\\  -.\\ \\   /\\ \\   /\\  ___\\   /\\ \\_\\ \\   /\\  ___\\   /\\ \\       /\\ \\       \n");
    printf("\\ \\ \\-./\\ \\  \\ \\ \\  \\ \\ \\-.  \\  \\ \\ \\  \\ \\___  \\  \\ \\  __ \\  \\ \\  __\\   \\ \\ \\____  \\ \\ \\____  \n");
    printf(" \\ \\_\\ \\ \\_\\  \\ \\_\\  \\  \\_\\ \\_\\  \\ \\_\\  \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\ \n");
    printf("  \\/_/  \\/_/   \\/_/   \\/_/ \\/_/   \\/_/   \\/_____/   \\/_/\\/_/   \\/_____/   \\/_____/   \\/_____/ \n\n\n");
    printf("\033[0m");
    printf("\033[0;34m");
    //printf("\t\t\t\t    -- IAKRY  X  HKHALIL --\n\n\n");
}

// SIGNALS

/*// void	handle_sig(int sig)
// {
// 	(void)sig;
// 	rl_replace_line("", 0);
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_redisplay();
// }
void errors(char *msg)
{
    printf("%s\n", msg);
    //clean everything
    exit(1);
}

void    executor(cmd *result_tree, env *env, int flag)
{
    int p[2];
    int id1;
    int id2;
    int open_fd;
    pip *tree1;
    redir *tree2;
    exec *tree3;

    if (result_tree->type == '|')
    {
        tree1 = (pip *)result_tree;
        if (pipe(p) < 0)
            errors("pipe error");
        id1 = fork();
        if (id1 < 0)
            errors("fork error");
        if (id1 == 0)
        {
            close(p[1]);
            dup2(p[0], 0);
            executor(tree1->right,env, flag);
            close(p[0]);
            return ;
        }
        id2 = fork();
        if (id2 == 0)
        {
            close(p[0]);
            dup2(p[1], 1);
            executor(tree1->left,env, flag);
            close(p[1]);
            return ;
        }
        close(p[0]);
        close(p[1]);
        wait(0);
        wait(0);
        return ;
     }
    else if (result_tree->type == '>')
    {
        tree2 = (redir *)result_tree;
        open_fd = open(tree2->file, tree2->mode);
        if (open_fd < 0)
            errors("open error");
        dup2(open_fd, tree2->fd);
        close(open_fd);
        executor(tree2->cmd, env, flag);
        return ;
    }
    else
    {
        tree3 = (exec *)result_tree;
       // execve((tree3->argv)[0], tree3->argv, env->path);
       // errors("execve error");
        //
        char *p;
        int i = -1;

        while (env->path[++i])
        {
            p = ft_strjoin(ft_strjoin(env->path[i], "/"), tree3->argv[0]);
            if (access(p, F_OK) != -1)
            {
                execve(p, tree3->argv, env->path);
                return ;
            }
        }
        return ;
    } 
}*/