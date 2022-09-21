/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:26:29 by iakry             #+#    #+#             */
/*   Updated: 2022/09/21 18:12:08 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int gettoken(char **ss, char *es, char **q, char **eq)
{
    char *s;
    int ret;

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
        //add qoutes heere
        ret = 'a';
        while (s < es && !ft_strchr(" \t\r\n\v", *s) && !ft_strchr("<|>", *s))
            s++;
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