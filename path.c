/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:07:20 by iakry             #+#    #+#             */
/*   Updated: 2022/09/17 18:13:29 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *envpath(char **env)
{
    int i = 0;
    t_env *envp;

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