/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:10:50 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/21 01:30:39 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int is_white_space(int c)
{
    if (c == ' ' || c == '\n' || c == '\v'|| c == '\t' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

char    *ft_env_name(char *s)
{
    int i = 0;

    while (s[i] && (s[i] != '$') && !is_white_space(s[i]) && (ft_isalpha(s[i]) || ft_isdigit(s[i])))
        i++;
    return (ft_substr(s, 0, i));
}

char    *expander(char *arg)
{
    char    *new_arg;
    char    *v;
    char    *c;
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
            else
            {
                c = ft_env_name(&arg[i + 1]);
                if (getenv(c))
                {
                    v = getenv(c);
                    //replace
                    new_arg = ft_strjoin(ft_strjoin(ft_substr(arg, 0, i), v), &arg[i + ft_strlen(c) + 1]);
                    free(arg);
                    free(c);
                    arg = ft_strdup(new_arg);
                    free(new_arg);
                    //skip
                    i = i + ft_strlen(v);
                }
                else if (c[0])
                {
                    new_arg = ft_strjoin(ft_substr(arg, 0, i), &arg[i + ft_strlen(c) + 1]);
                    free(arg);
                    arg = ft_strdup(new_arg);
                    free(new_arg);
                    i = i + ft_strlen(c);
                    free(c);
                }
                else
                    i++;
            }
        }
        else
            i++;
    }
    return (arg);
}