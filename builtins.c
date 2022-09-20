/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:03:10 by iakry             #+#    #+#             */
/*   Updated: 2022/09/20 01:13:38 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_cd(char *buff, int index)
{    
    while (--index >= 0)
        if (!ft_strchr(" \t\v\f\r\t", buff[index]) && !ft_strchr("|", buff[index]))
            return 0;
    return 1;
}

int cd(char *buff)
{
    int i = -1;
    char *s = buff;

    while (s[++i]){
        if (!ft_strncmp(&s[i], "cd ", 3) && check_cd(s, i))
        {
            if (!ft_strchr(&s[i], '|'))
                if (chdir(getpath(&s[i]))){
                    perror("cd");
                    free(buff);
                    return (0);
                }
            return (1);
        }
    }
    return (1);
}
