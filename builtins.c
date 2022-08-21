/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iakry <iakry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 13:03:10 by iakry             #+#    #+#             */
/*   Updated: 2022/08/16 15:49:46 by iakry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_cd(char *buff, int index)
{    
    while (--index >= 0)
        if (!strchr(" \t\v\f\r\t", buff[index]) && !strchr("|", buff[index]))
            return 0;
    return 1;
}

int cd(char *buff)
{
    int i = -1;
    char *s = buff;

    while (s[++i]){
        if (!strncmp(&s[i], "cd ", 3) && check_cd(s, i))
        {
            if (!strchr(&s[i], '|'))
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
