/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:41:25 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 21:12:15 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parent_builtin_exit(t_cmd *tree)
{
	t_exec	*cmd;

	cmd = (t_exec *)tree;
	if (!ft_strcmp(cmd->argv[0], "exit"))
	{
		ft_exit(cmd);
		clean(tree);
		return (1);
	}
	return (0);
}

int	parent_builtin_cd(t_cmd *tree, t_envvar **env)
{
	t_exec	*cmd;

	cmd = (t_exec *)tree;
	if (!ft_strcmp(cmd->argv[0], "cd"))
	{
		ft_cd(cmd, *env);
		clean(tree);
		return (1);
	}
	return (0);
}

int	parent_builtin_unset(t_cmd *tree, t_envvar **env)
{
	t_exec	*cmd;

	cmd = (t_exec *)tree;
	if (!ft_strcmp(cmd->argv[0], "unset"))
	{
		ft_unset(cmd, env);
		if (g_var == -2)
			g_var = 1;
		else
			g_var = 0;
		clean(tree);
		return (1);
	}
	return (0);
}

int	parent_builtin_export(t_cmd *tree, t_envvar **env)
{
	t_exec	*cmd;

	cmd = (t_exec *)tree;
	if (!ft_strcmp(cmd->argv[0], "export"))
	{
		ft_export(cmd, env);
		if (g_var == -2)
			g_var = 1;
		else
			g_var = 0;
		clean(tree);
		return (1);
	}
	return (0);
}

int	parent_builtin(char *buff, t_envvar **env)
{
	t_cmd	*tree;
	t_exec	*cmd;

	tree = parsecmd(buff, env, 0);
	if (tree->type == EXEC)
	{
		cmd = (t_exec *)tree;
		if (parent_builtin_exit(tree))
			return (1);
		else if (parent_builtin_cd(tree, env))
			return (1);
		else if (parent_builtin_unset(tree, env))
			return (1);
		else if (parent_builtin_export(tree, env))
			return (1);
	}
	clean(tree);
	return (0);
}
