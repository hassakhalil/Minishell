/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_builtin_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:50:01 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 10:53:53 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
