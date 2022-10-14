/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:13:17 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/14 20:13:31 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int errno ;

void errors(char *name, int flag)
{
    if (flag == 4 && errno != 2)
    {
        if (errno == 22)
        {
            write(2, name, ft_strlen(name));
            write(2, ": is a directory\n", 18);
            exit(126);
        }
        perror(name);
        exit(126);
    }
    if (flag == 2 || flag == 3)
    {
        write(2,name, ft_strlen(name));
        if (flag == 2)
            write(2, ": Permission denied\n", 21);
        else
             write(2, ": No such file or directory\n", 29);
        exit(1);
    }
    if (errno == 2 || errno == 13)
    {
        if (ft_strchr(name, '/'))
                perror(name);
        else
        {
            write(2, name, ft_strlen(name));
            write(2, ": command not found\n",21);
        }
        if (errno == 2)
            exit(127);
        else if (errno == 13)
            exit(126);
    } 
}