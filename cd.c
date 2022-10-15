/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 04:32:05 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 04:41:33 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(t_exec *cmd, t_envvar *env)
{
	if (cmd->argv[1])
	{
		if (chdir(cmd->argv[1]))
		{
			write(2, "cd: ", 5);
			perror(cmd->argv[1]);
			GLOBAL = 1;
			return ;
		}
	}
	if (!(cmd->argv[1]))
	{
		while (env)
		{
			if (!ft_strcmp(env->name, "HOME"))
				chdir(env->value);
			env = env->next;
		}
		GLOBAL = 0;
	}
}
