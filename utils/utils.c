/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:34:14 by iakry             #+#    #+#             */
/*   Updated: 2022/10/01 11:21:18 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	forkk(void)
{
	int pid;
	
	pid = fork();
	if(pid == -1)
    {
        printf("fork failed !");
        exit(1);
    }
	return pid;
}

char	*mkcopy(char *s, char *es)
{
	int n;
	
	n = es - s;
	char *c = malloc(n+1);
	if (!c)
		perror("error");
	ft_strncpy(c, s, n);
	c[n] = 0;
	return c;
}

t_cmd* redircmd(t_cmd *subcmd, char *file, int mode, int type)
{
    t_redir *cmd;
    
    cmd = malloc(sizeof(*cmd));
    //memset(cmd, 0, sizeof(*cmd));
    cmd->type = REDIR;
    cmd->cmd = subcmd;
    cmd->file = ft_strdup(file);
    cmd->mode = mode;
    if (type == '<' || type == '*')
        cmd->fd = 0;
    else
        cmd->fd = 1;
    return ((t_cmd*)cmd);
}

t_cmd* execcmd(void)
{
    t_exec *cmd;
    
    cmd = malloc(sizeof(*cmd));
    //memset(cmd, 0, sizeof(*cmd));
    cmd->type = EXEC;
    return (t_cmd*)cmd;
}

t_cmd   *pipecmd(t_cmd *left, t_cmd *right)
{
    t_pip *cmd;
    
    cmd = malloc(sizeof(*cmd));
   // memset(cmd, 0, sizeof(*cmd));
    cmd->type = PIPE;
    cmd->left = left;
    cmd->right = right;
    return ((t_cmd*)cmd);
}

void    hd_handler(int sig)
{
        sig = 1;
        write(1, "\n", 1);
        exit(sig);
}

char    *create_heredoc(char *delimiter)
{
    int fd;
    int id;
    char *buff;
    char *path;
    int exits;

    path = ft_strjoin("/tmp/", delimiter);
    id  = forkk();
    if (id == 0)
    {
        signal(SIGQUIT,SIG_IGN);
	    signal(SIGINT, hd_handler);
        fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0666);
        buff = readline("> ");
        while(buff && ft_strcmp(buff, delimiter))
        {
            write(fd, buff, ft_strlen(buff));
             write(fd, "\n", 1);
            free(buff);
            buff = readline("> ");
        }
        if (buff)
            free(buff);
        close(fd);
        exit(0);
    }
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    waitpid(id, &exits, 0);
    if (WEXITSTATUS(exits) == 1)
        exit(1);
    return (path);
}