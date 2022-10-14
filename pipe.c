/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 00:22:59 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 00:44:16 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    create_pipe(int p[2])
{
    if (pipe(p) < 0)
        perror("pipe error");
}

void    ft_wait(int id)
{
    int     last;
    int     mid;

    waitpid(id, &last , 0);
    while(wait(&mid) > 0)
    {
        if ((WTERMSIG(mid) == 3 || WTERMSIG(mid) == 2) && (WTERMSIG(last) != 3 && WTERMSIG(last) != 2))
        GLOBAL = -1;
    }
    exit(WEXITSTATUS(last));
}

void    ft_pipe(t_cmd *tree, int *flag_out, int *flag_in, t_envvar **env_list)
{
    t_pip     *tree1;
    int     p[2];
    int     id;

    tree1 = (t_pip *)tree;
    create_pipe(p);
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
    ft_wait(id);
}