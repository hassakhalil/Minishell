/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:34:14 by iakry             #+#    #+#             */
/*   Updated: 2022/10/17 09:28:21 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	forkk(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("fork failed !");
		exit(1);
	}
	return (pid);
}

char	*mkcopy(char *s, char *es)
{
	int		n;
	char	*c;

	n = es - s;
	c = malloc(n + 1);
	if (!c)
		perror("error");
	ft_strncpy(c, s, n);
	c[n] = 0;
	return (c);
}

t_cmd	*redircmd(t_cmd *subcmd, char *file, int mode, int type)
{
	t_redir	*cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->mode = mode;
	if (type == '<' || type == '*')
		cmd->fd = 0;
	else
		cmd->fd = 1;
	return ((t_cmd *)cmd);
}

t_cmd	*execcmd(void)
{
	t_exec	*cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*pipecmd(t_cmd *left, t_cmd *right)
{
	t_pip	*cmd;

	cmd = malloc(sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd *)cmd);
}
