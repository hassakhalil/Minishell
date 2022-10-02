/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 05:09:26 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/02 19:27:57 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *quote_remover(char *s)
{
    int i = 0;
    int j = 0;
    int c;
    char    *new;
    
    new = malloc(sizeof(char) * ft_strlen(s) + 1);
    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '\"')
        {
            c = s[i];
            i++;
            while (s[i] && s[i] != c)
            {
                new[j] = s[i];
                i++;
                j++;
            }
            i++;
        }
        else
        {
            new[j] = s[i];
            i++;
            j++;
        } 
    }
    new[j] = 0;
    free(s);
    return (new);
}