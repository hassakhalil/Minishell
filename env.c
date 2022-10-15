/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 04:47:35 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 04:51:33 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_for_env(char *s)
{
	if (ft_strlen(s) != 3)
		return (0);
	if (ft_tolower(s[0]) == 'e'
		&& ft_tolower(s[1]) == 'n' && ft_tolower(s[2]) == 'v')
		return (1);
	return (0);
}

void	ft_env(t_exec *cmd, t_envvar *env)
{
	if (cmd->argv[1])
	{
		printf("env: %s: No such file or directory\n", cmd->argv[1]);
		exit(127);
	}
	else
	{
		while (env)
		{
			if (env->value)
				printf("%s=%s\n", env->name, env->value);
			env = env->next;
		}
	}
	exit(0);
}
