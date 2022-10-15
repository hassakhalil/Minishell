/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 01:14:08 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 01:17:20 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_exec(t_cmd *tree, t_envvar **env_list)
{
    DIR *dir;
    int     i;
    t_exec    *tree3;
    char *str = NULL;
    char    *s;

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