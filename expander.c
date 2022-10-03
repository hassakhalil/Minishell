/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:10:50 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/03 19:54:38 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

    while (s[i] && (s[i] != '$' && !is_white_space(s[i]) && s[i] != '\'' && s[i] != '\"') && (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_'))
        i++;
    return (ft_substr(s, 0, i));
}

char    *expander(char *arg)
{
    char    *new_arg;
    char    *v;
    char    *c;
    int     i = 0;
    int     quote = 0;

    while (arg[i])
    {
        if (arg[i] == '\'' || arg[i] == '\"')
        {
            if (!quote)
                quote = arg[i];
            else
                if (arg[i] == quote)
                    quote = 0;
        }
        if (quote != '\'' && arg[i] == '$')
        {
                if (arg[i + 1] && arg[i + 1] == '?')
                {
                    if (GLOBAL == 58)
                        GLOBAL = 258;
                    new_arg = ft_strjoin3(ft_strjoin3(ft_substr(arg, 0, i), ft_itoa(GLOBAL)),&arg[i + 2]);
                    free(arg);
                    arg = ft_strdup(new_arg);
                    free(new_arg);
                    i++;
                }
                else
                {
                    c = ft_env_name(&arg[i + 1]);
                    if (getenv(c))
                    {
                        v = getenv(c);
                        new_arg = ft_strjoin3(ft_strjoin3(ft_substr(arg, 0, i), v), &arg[i + ft_strlen(c) + 1]);
                        free(arg);
                        arg = ft_strdup(new_arg);
                        free(new_arg);
                        i = i + ft_strlen(v);
                    }
                    else if (c[0])
                    {
                        new_arg = ft_strjoin3(ft_substr(arg, 0, i), &arg[i + ft_strlen(c) +1]);
                        free(arg);
                        arg = ft_strdup(new_arg);
                        free(new_arg);
                    }
                    else if(arg[i + 1] && (arg[i + 1] == '\'' || arg[i + 1] == '\"'))
                    {
                        new_arg = ft_strjoin3(ft_substr(arg, 0, i), &arg[i + 1]);
                        free(arg);
                        arg = ft_strdup(new_arg);
                        free(new_arg);
                    }
                    else
                        i++;
                    free(c);
                }
        }
        else
            i++;
    }
    return (arg);
}