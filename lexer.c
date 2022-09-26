/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:26:29 by iakry             #+#    #+#             */
/*   Updated: 2022/09/26 21:55:59 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int gettoken(char **ss, char *es, char **q, char **eq)
{
    char *s;
    int ret;
    int c = 0;

    s = *ss;
    while(s < es && ft_strchr(" \t\r\n\v", *s))
        s++;
    if(q)
        *q = s;
    ret = *s;
    if (*s == 0)
        return ret;
    else if (*s == '|')
        s++;
    else if (*s == '>')
    {
        s++;
        if (*s == '>')
        {
            s++;
            ret = '+';
        }
    }
    else if (*s == '<')
    {
        s++;
        if (*s == '<')
        {
            s++;
            ret = '*';
        }
    }
    else
    {
        ret = 'a';
        while (s < es && !ft_strchr(" \t\r\n\v", *s) && !ft_strchr("<|>", *s))
        {
            if (*s == '\'' || *s == '\"')
            {
                c = *s;
                s++;
                while(s < es && *s != c)
                    s++;
                if (s == es)
                {
                    write(2, "syntax error\n", 14);
                    exit (1);
                }
            }
            if (s!= es)
                s++;
        }
    }
    if(eq)
        *eq = s;
    while(s < es && ft_strchr(" \t\r\n\v", *s))
        s++;
    *ss = s;
    return ret;
}

int peek(char **ss, char *es, char *toks)
{
    char *s;

    s = *ss;
    while(s < es && ft_strchr(" \t\r\n\v", *s))
        s++;
    *ss = s;
    return (*s && ft_strchr(toks, *s));
}