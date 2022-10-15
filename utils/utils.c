/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:34:14 by iakry             #+#    #+#             */
/*   Updated: 2022/10/15 03:26:25 by hkhalil          ###   ########.fr       */
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
    cmd->file = file;
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

void    create_heredoc(char *delimiter)
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
        //debug
        dprintf(2, "child 2 pid = { %d }\n", getpid());
        //end debug
        signal(SIGQUIT,SIG_IGN);
	    signal(SIGINT, hd_handler);
        fd = open(path, O_WRONLY|O_CREAT|O_TRUNC, 0666);
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
    free(delimiter);
    free(path);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, SIG_IGN);
    waitpid(id, &exits, 0);
    if (WEXITSTATUS(exits) == 1)
        exit(1);
}

char    **list_to_table(t_envvar *env)
{
    int n = ft_lstsize(env);
    int i = 0;
    char    **tab=malloc(sizeof(char *) * (n +1));

    while (env)
    {
        if (env->value)
        {
            tab[i] = ft_strjoin3(ft_strjoin(env->name, "="), env->value);
            i++;
        }
        env = env->next;
    }
    tab[i] = 0;
    return(tab);
}

char    *my_getenv(char *s, t_envvar *env)
{
    while (env)
    {
        if (!ft_strcmp(env->name, s))
            return(env->value);
        env = env->next;
    }
    return (0);
}

char	*ft_env_name(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != '$' && !is_white_space(s[i])
			&& s[i] != '\'' && s[i] != '\"')
		&& (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_'))
		i++;
	return (ft_substr(s, 0, i));
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_white_space(int c)
{
	if (c == ' ' || c == '\n' || c == '\v'
		|| c == '\t' || c == '\f' || c == '\r')
		return (1);
	return (0);
}