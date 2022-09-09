/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:26:29 by iakry             #+#    #+#             */
/*   Updated: 2022/09/09 17:14:27 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int gettoken(char **ss, char *es, char **q, char **eq)
{
    char *s;
    int ret;

    s = *ss;
    while(s < es && strchr(" \t\r\n\v", *s))
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
        if (*s++ == '>')
            ret = '+';
    }
    else if (*s == '<')
    {
        s++;
        if (*s++ == '<')
            ret = '*';
    }
    else
    {
        ret = 'a';
        while (s < es && !strchr(" \t\r\n\v", *s) && !strchr("<|>", *s))
            s++;
    }
    if(eq)
        *eq = s;
    while(s < es && strchr(" \t\r\n\v", *s))
        s++;
    *ss = s;
    return ret;
}

int peek(char **ss, char *es, char *toks)
{
    char *s;
    
    s = *ss;
    while(s < es && strchr(" \t\r\n\v", *s))
        s++;
    *ss = s;
    return (*s && strchr(toks, *s));
}