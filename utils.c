/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:34:14 by iakry             #+#    #+#             */
/*   Updated: 2022/09/11 17:35:04 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t  ft_strlen(char *s)
{
    size_t i;

    i = 0;
    while (s[i])
		i++;
    return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	if (s[i] == c)
		return ((char *)&s[i]);
	return (0);
}

int	forkk(void)
{
	int pid;
	
	pid = fork();
	if(pid == -1)
		errors("fork error\n");
	return pid;
}

char	*mkcopy(char *s, char *es)
{
	int n;
	
	n = es - s;
	char *c = malloc(n+1);
	if (!c)
		perror("error");
	strncpy(c, s, n);
	c[n] = 0;
	return c;
}

struct cmd* redircmd(struct cmd *subcmd, char *file, int mode, int type)
{
    struct redircmd *cmd;
    
    cmd = malloc(sizeof(*cmd));
    //memset(cmd, 0, sizeof(*cmd));
    cmd->type = REDIR;
    cmd->cmd = subcmd;
    cmd->file = strdup(file);
    cmd->mode = mode;
    if (type == '<' || type == '*')
        cmd->fd = 0;
    else
        cmd->fd = 1;
    return ((struct cmd*)cmd);
}

struct cmd* execcmd(void)
{
    struct execcmd *cmd;
    
    cmd = malloc(sizeof(*cmd));
    //memset(cmd, 0, sizeof(*cmd));
    cmd->type = EXEC;
    return (struct cmd*)cmd;
}

struct cmd* pipecmd(struct cmd *left, struct cmd *right)
{
    struct pipecmd *cmd;
    
    cmd = malloc(sizeof(*cmd));
   // memset(cmd, 0, sizeof(*cmd));
    cmd->type = PIPE;
    cmd->left = left;
    cmd->right = right;
    return ((struct cmd*)cmd);
}

char    *create_heredoc(char *delimiter)
{
    int fd;
    char *deli;
    char *buff;
    char *path;

    path = ft_strjoin("/tmp/", delimiter);
    deli = ft_strjoin(delimiter, "\n");
    fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0666);
    buff = get_next_line(0);
    while(buff && strcmp(deli, buff))
    {
        write(fd, buff, strlen(buff));
        free(buff);
        buff = get_next_line(0);
    }
    close(fd);
    return (path);
}