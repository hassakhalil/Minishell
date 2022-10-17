/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 20:41:25 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 10:13:01 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_in_files0(t_cmd *redir, int *flag)
{
	t_redir	*tmp;
	int		fd;

	tmp = (t_redir *)redir;
	fd = open(tmp->file, tmp->mode);
	if (fd < 0)
	{
		close(fd);
		if (!access(tmp->file, F_OK))
			errors(tmp->file, 10);
		else
			errors(tmp->file, 11);
		*flag = 1;
	}
	close(fd);
}

void	find_in_redir0(t_cmd *tree, int *flag)
{
	t_redir	*tree2;

	if (tree->type == REDIR)
	{
		tree2 = (t_redir *)tree;
		find_in_redir0(tree2->cmd, flag);
		if (tree2->fd == 0)
			check_in_files0(tree, flag);
	}
}

void	open_files(t_cmd *tree, t_envvar **env_list)
{
	t_redir	*tree2;
	int		open_fd;

	tree2 = (t_redir *)tree;
	open_fd = open(tree2->file, tree2->mode, 0666);
	if (open_fd < 0)
		return ;
	close(open_fd);
	if (tree2->cmd->type == REDIR)
		open_files(tree2->cmd, env_list);
}

void	parent_builtin_exit(t_cmd *tree, int *flag)
{
	t_exec	*cmd;

	cmd = (t_exec *)tree;
	if (!ft_strcmp(cmd->argv[0], "exit"))
	{
		ft_exit(cmd);
		*flag = 1;
	}
}

void	parent_builtin_cd(t_cmd *tree, t_envvar **env, int *flag)
{
	t_exec	*cmd;

	cmd = (t_exec *)tree;
	if (!ft_strcmp(cmd->argv[0], "cd"))
	{
		ft_cd(cmd, *env);
		*flag = 1;
	}
}

void	parent_builtin_unset(t_cmd *tree, t_envvar **env, int *flag)
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
		*flag = 1;
	}
}

void	parent_builtin_export(t_cmd *tree, t_envvar **env, int *flag)
{
	t_exec	*cmd;

	cmd = (t_exec *)tree;
	if (!ft_strcmp(cmd->argv[0], "export") && cmd->argv[1])
	{
		ft_export(cmd, env);
		if (g_var == -2)
			g_var = 1;
		else
			g_var = 0;
		*flag = 1;
	}
}

int	parent_builtin(char *buff, t_envvar **env)
{
	t_cmd	*tree;
	t_cmd	*tmp;
	int		id;
	int		exits;
	int		flag;

	flag = 0;
	id = forkk();
	if (id == 0)
	{
		g_var = -100;
		tree = parsecmd(buff, env);
		exit(0);
	}
	wait(&exits);
	if (WEXITSTATUS(exits))
	{
		g_var = WEXITSTATUS(exits);
		return (1);
	}
	tree = parsecmd(buff, env);
	tmp = tree;
	if (tree->type != PIPE)
	{
		find_in_redir0(tmp, &flag);
		if (!flag)
		{
			tmp = tree;
			if (tree->type == REDIR)
				open_files(tmp, env);
			tmp = tree;
			while (tmp->type != EXEC)
				tmp = ((t_redir *)tmp)->cmd;
			parent_builtin_exit(tmp, &flag);
			if (!flag)
				parent_builtin_cd(tmp, env, &flag);
			if (!flag)
				parent_builtin_unset(tmp, env, &flag);
			if (!flag)
				parent_builtin_export(tmp, env, &flag);
		}
	}
	clean(tree);
	if (flag)
		return (1);
	return (0);
}
