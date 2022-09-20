/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:10:50 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/20 23:59:55 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_white_space(int c)
{
    if (c == ' ' || c == '\n' || c == '\v'|| c == '\t' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

char    *ft_env_name(char *s)
{
    int i = 0;

    while (s[i] && !is_white_space(s[i]))
        i++;
    return (ft_substr(s, 0, i));
}

char    *expander(char *arg)
{
    char    *new_arg;
    char    *v;
    int     i = 0;

    while (arg[i])
    {
        if (arg[i] == '$')
        {
            if (arg[i + 1] && arg[i + 1] == '?')
            {
                //repplace "$?" with GLOBAL in new_arg
                new_arg = ft_strjoin(ft_strjoin(ft_substr(arg, 0, i), ft_itoa(GLOBAL)),&arg[i + 2]);
                free(arg);
                arg = ft_strdup(new_arg);
                free(new_arg);
                //free the left arg in strjoin
                //skip 
                i++;
            }
            else if (getenv(ft_env_name(&arg[i])))
            {
                v = getenv(ft_env_name(&arg[i]));
                //replace
                new_arg = ft_strjoin(ft_strjoin(ft_substr(arg, 0, i), v), &arg[i + ft_strlen(v) + 1]);
                free(arg);
                arg = ft_strdup(new_arg);
                free(new_arg);
                //skip
                i = i + ft_strlen(v) + 1;
            }
            else
                i++;
        }
        else
            i++;
    }
    return (arg);
}