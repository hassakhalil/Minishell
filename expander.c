/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:10:50 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/24 05:23:50 by hkhalil          ###   ########.fr       */
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

    while (s[i] && (s[i] != '$') && !is_white_space(s[i]) && (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_'))
        i++;
    return (ft_substr(s, 0, i));
}

char    *expander(char **arg)
{
    char    *new_arg;
    char    *v;
    char    *c;
    int     i = 0;
    int     k = 0;

    while (arg[0][i])
    {
        if (arg[0][i] == '$') //and  dollar[k] = expand // k++
        {
            if (arg[1][k] == '\"')
            {
                if (arg[0][i + 1] && arg[0][i + 1] == '?')
                {
                    if (GLOBAL == 58)
                        GLOBAL = 258;
                    new_arg = ft_strjoin(ft_strjoin(ft_substr(arg[0], 0, i), ft_itoa(GLOBAL)),&arg[0][i + 2]);
                    free(arg[0]);
                    arg[0] = ft_strdup(new_arg);
                    free(new_arg);
                    i++;
                }
                else
                {
                    c = ft_env_name(&arg[0][i + 1]);
                    if (getenv(c))
                    {
                        v = getenv(c);
                        new_arg = ft_strjoin(ft_strjoin(ft_substr(arg[0], 0, i), v), &arg[0][i + ft_strlen(c) + 1]);
                        free(arg[0]);
                        free(c);
                        arg[0] = ft_strdup(new_arg);
                        free(new_arg);
                        i = i + ft_strlen(v);
                    }
                    else if (c[0])
                    {
                        new_arg = ft_strjoin(ft_substr(arg[0], 0, i), &arg[0][i + ft_strlen(c) +1]);
                        free(arg[0]);
                        arg[0] = ft_strdup(new_arg);
                        free(new_arg);
                        free(c);
                    }
                    else
                        i++;   
                }
            }
            i++;
            k++;   
        }
        else
            i++;
    }
    free(arg[1]);
    free(arg[2]);
    return (arg[0]);
}