/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 05:09:26 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/23 06:38:08 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *quote_remover(char *s)
{
    //char *dollars = malloc(number of dollars );
    int i = 0;
    int j = 0;
    int c;
    char    *new =malloc(sizeof(char)*ft_strlen(s) + 1);

    while (s[i])
    {
        if (s[i] == '\'' || s[i] == '\"')
        {
            c = s[i];
            i++;
            while (s[i] != c)
            {
                //if s[i] == $
                    //dollars[k] = c;
                    //k++
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
    return (new);
}