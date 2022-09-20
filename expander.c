/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:10:50 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/20 20:32:01 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    expander(char *arg)
{
    int i = 0;

    while (arg[i])
    {
        if (arg[i] == '$')
        {
            i++;
            if (arg[i] && arg[i] == '?')
                //repplace "$?" with GLOBAL
            else if (getenv(ft_env_name(x)))
                //replace
            i++;
        }
    }
}