/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 04:21:58 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 04:29:18 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_for_echo(char *s)
{
	if (ft_strlen(s) != 4)
		return (0);
	if (ft_tolower(s[0]) == 'e' && ft_tolower(s[1]) == 'c'
		&& ft_tolower(s[2]) == 'h' && ft_tolower(s[3]) == 'o')
		return (1);
	return (0);
}

int	options(char *s)
{
	int	i;

	i = 0;
	if (s[i] != '-')
		return (0);
	i++;
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(t_exec *cmd)
{
	int	i;
	int	noption;

	i = 1;
	noption = 0;
	if (cmd->argv[i])
	{
		while (options(cmd->argv[i]))
		{
			noption = 1;
			i++;
		}
		while (cmd->argv[i])
		{
			printf("%s", cmd->argv[i]);
			i++;
			if (cmd->argv[i])
				printf(" ");
		}
	}
	if (noption == 0)
		printf("\n");
	exit(0);
}
