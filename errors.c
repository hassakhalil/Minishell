/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:13:17 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 09:49:34 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors1(char *name)
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

void	errors2(char *name, int flag)
{
	write(2, name, ft_strlen(name));
	if (flag == 2)
		write(2, ": Permission denied\n", 21);
	else
		write(2, ": No such file or directory\n", 29);
	exit(1);
}

void	errors3(char *name)
{
	if (ft_strchr(name, '/'))
		perror(name);
	else
	{
		write(2, name, ft_strlen(name));
		write(2, ": command not found\n", 21);
	}
	if (errno == 2)
		exit(127);
	else if (errno == 13)
		exit(126);
}

void	errors4(char *name, int flag)
{
	write(2, name, ft_strlen(name));
	if (flag == 10)
		write(2, ": Permission denied\n", 21);
	else
		write(2, ": No such file or directory\n", 29);
	g_var = 1;
}

void	errors(char *name, int flag)
{
	if (flag == 20 || flag == 21 || flag == 22 || flag == 23)
		errors5(flag);
	if (flag == 10 || flag == 11)
	{
		errors4(name, flag);
		return ;
	}
	if (flag == 4 && errno != 2)
		errors1(name);
	if (flag == 2 || flag == 3)
		errors2(name, flag);
	if (errno == 2 || errno == 13)
		errors3(name);
}
