/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 05:09:26 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/23 23:49:19 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int dollars(char *s)
{
    int i = 0;
    int k = 0;

    while (s[i])
    {
        if (s[i] == '$')
            k++;
        i++;
    }
    return(k);
}

char    **quote_remover(char *s)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int c;
    char    **new = malloc(sizeof(char *) * 3);
    
    new[0] = malloc(sizeof(char) * ft_strlen(s) + 1);
    new[1] = malloc(sizeof(char) * dollars(s) + 1);
    while (s[i])
    {
        if (s[i] == '$')
        {
            new[1][k] = '\"';
            k++;
        }
        if (s[i] == '\'' || s[i] == '\"')
        {
            c = s[i];
            i++;
            while (s[i] != c)
            {
                if (s[i] == '$')
                {
                    new[1][k] = c;
                    k++;
                }
                new[0][j] = s[i];
                i++;
                j++;
            }
            i++;
        }
        else
        {
            new[0][j] = s[i];
            i++;
            j++;
        }
        
    }
    new[0][j] = 0;
    new[1][k] = 0;
    new[2] = 0;
    return (new);
}