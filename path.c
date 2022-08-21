/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iakry <iakry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:07:20 by iakry             #+#    #+#             */
/*   Updated: 2022/08/13 14:29:00 by iakry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct env *envpath(char **env)
{
    int j;
    int i = 0;
    struct env *envp;

    envp = malloc(sizeof(*envp));
    while(env[i])
    {
        while (*env[i])
        {
            if (!strncmp(env[i], "PATH=", 5))
                envp->path = ft_split(env[i]+5, ':');
            env[i]++;
        }
        i++;
    }
    return envp;
}

char *getpath(char *buff)
{
    char *s = buff;
    char path[100];
    int i = 0;
    
    if (!strncmp(s, "cd ", 3))
    {
        s = s+3;
        while (*s == ' ')
            s++;
        while (*s != ' ' && *s)
            path[i++] = *s++;
        path[i] = 0;
        s = path;
        return (s);
    }
    return NULL;
}