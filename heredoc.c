/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:08:25 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 09:17:23 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hd_handler(int sig)
{
	sig = 1;
	write(1, "\n", 1);
	exit(sig);
}

void	heredoc_child(char *delimiter, char *path)
{
	int		fd;
	char	*buff;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, hd_handler);
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	free(path);
	buff = readline("> ");
	while (buff && ft_strcmp(buff, delimiter))
	{
		write(fd, buff, ft_strlen(buff));
		write(fd, "\n", 1);
		free(buff);
		buff = readline("> ");
	}
	free(delimiter);
	close(fd);
	if (buff)
		free(buff);
	exit(0);
}

char	*create_heredoc(char *delimiter)
{
	int		id;
	char	*path;
	int		exits;

	path = ft_strjoin("/tmp/", delimiter);
	id = forkk();
	if (id == 0)
		heredoc_child(delimiter, path);
	free(delimiter);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	waitpid(id, &exits, 0);
	if (WEXITSTATUS(exits) == 1)
		exit(1);
	return (path);
}
