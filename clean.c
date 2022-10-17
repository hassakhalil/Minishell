/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:31:23 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 09:46:00 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_envvar **env)
{
	while (env && *env)
	{
		free((*env)->name);
		if ((*env)->value)
			free((*env)->value);
		*env = (*env)->next;
	}
}

void	free_exec(t_exec *node)
{
	int	i;

	i = 0;
	while (node->argv[i])
	{
		free(node->argv[i]);
		i++;
	}
	free(node);
}

void	free_redir(t_redir *node)
{
	free(node->file);
	free(node);
}

void	free_pipe(t_pip *node)
{
	free(node);
}

void	clean(t_cmd *tree)
{
	t_pip	*tree1;
	t_redir	*tree2;
	t_exec	*tree3;

	if (tree->type == PIPE)
	{
		tree1 = (t_pip *)tree;
		clean(tree1->left);
		clean(tree1->right);
		free_pipe(tree1);
	}
	else if (tree->type == REDIR)
	{
		tree2 = (t_redir *)tree;
		clean(tree2->cmd);
		free_redir(tree2);
	}
	else
	{
		tree3 = (t_exec *)tree;
		free_exec(tree3);
	}
}
