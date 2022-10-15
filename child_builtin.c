/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:02:29 by iakry             #+#    #+#             */
/*   Updated: 2022/10/15 20:58:55 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_builtin_cd(t_exec *tree3, t_envvar **env_list)
{
	if (!ft_strcmp(tree3->argv[0], "cd"))
	{
		ft_cd(tree3, *env_list);
		if (errno == 13 || errno == 2)
			exit(1);
		exit(0);
	}
	return (0);
}

int	child_builtin_export(t_exec *tree3, t_envvar **env_list)
{
	if (!ft_strcmp(tree3->argv[0], "export"))
	{
		ft_export(tree3, env_list);
		if (GLOBAL == -2)
			exit(1);
		exit(0);
	}
	return (0);
}

int	child_builtin_unset(t_exec *tree3, t_envvar **env_list)
{
	if (!ft_strcmp(tree3->argv[0], "unset"))
	{
		ft_unset(tree3, env_list);
		if (GLOBAL == -2)
			exit(1);
		exit (0);
	}
	return (0);
}

void	child_builtin(t_exec *tree3, t_envvar **env_list)
{
	if (!empty_cmd(tree3->argv[0]))
		exit(0);
	if (!ft_strcmp(tree3->argv[0], "exit"))
	{
		ft_exit(tree3);
		exit(GLOBAL);
	}
	else if (child_builtin_cd(tree3, env_list))
		;
	else if (ft_check_for_pwd(tree3->argv[0]))
		ft_pwd();
	else if (ft_check_for_echo(tree3->argv[0]))
		ft_echo(tree3);
	else if (ft_check_for_env(tree3->argv[0]))
		ft_env(tree3, *env_list);
	else if (child_builtin_export(tree3, env_list))
		;
	else if (child_builtin_unset(tree3, env_list))
		;
}
