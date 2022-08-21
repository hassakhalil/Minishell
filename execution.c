/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iakry <iakry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:08:47 by iakry             #+#    #+#             */
/*   Updated: 2022/08/16 15:27:01 by iakry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int run(struct execcmd *ecmd, struct env *envp)
{
    char *p;
    int i = -1;

    while (envp->path[++i])
    {
        p = ft_strjoin(ft_strjoin(envp->path[i], "/"), ecmd->argv[0]);
        if (access(p, F_OK) != -1)
        {
            execve(p, ecmd->argv, envp->path);
            return (1);
        }
    }
    return (0);
}

void runcmd(struct cmd *cmd, struct env *envp)
{
    int i = -1;
    int fd_redirect;
    int p_id;
    int fd_pipe[2];
    char cwd[100];
    struct execcmd *ecmd;
    struct pipecmd *pcmd;
    struct redircmd *rcmd;

    getcwd(cwd, 100);
    if (cmd->type == ' ')
    {
        ecmd = (struct execcmd*)cmd;
        
        if(ecmd->argv[0] == 0)
            exit(0);
        if(strcmp(ecmd->argv[0], "cd"))
            if (!run(ecmd, envp))
                perror("command not found");
    }
    
    if (cmd->type == '|')
    {
        pcmd = (struct pipecmd*)cmd;
        
        if (pipe(fd_pipe) < 0){
            perror("pipe");
            exit(0);
        }
        if ((p_id = fork()) < 0){
            perror("fork");
            exit(0);
        }
        else if (p_id == 0){
            // child process
            close(fd_pipe[1]);
            dup2(fd_pipe[0], STDIN_FILENO);
            runcmd(pcmd->right, envp);
            close(fd_pipe[0]);
        }
        else {
            close(fd_pipe[0]);
            dup2(fd_pipe[1], STDOUT_FILENO);
            runcmd(pcmd->left, envp);
            close(fd_pipe[1]);
            wait(&p_id);
        }
    }

    // if ((cmd->type == '<' || (cmd->type == '>')))
    // {
    //     rcmd = (struct redircmd *)cmd;
    //     fd_redirect = open(rcmd->file, rcmd->mode);
    //     if (fd_redirect < 0)
    //         perror("open error");
    //     dup2(fd_redirect, rcmd->fd);
    //     close(fd_redirect);
    //     runcmd(rcmd->cmd, envp);
    // }
    
    if ((cmd->type == '<' || (cmd->type == '>')))
    {
        rcmd = (struct redircmd*)cmd;
    
        if (rcmd->type == '>'){
            if ((fd_redirect = open(rcmd->file, rcmd->mode, 0666)) < 0){
            fprintf(stderr, "open %s has failed\n", rcmd->file);
            exit(0);
            }
        }
        else if (rcmd->type == '<'){
            if ((fd_redirect = open(rcmd->file, rcmd->mode)) < 0){
            fprintf(stderr, "open %s has failed\n", rcmd->file);
            exit(0);
            }
        }
        if (dup2(fd_redirect, rcmd->fd) < 0){
            fprintf(stderr, "dup2 has failed\n");
            exit(0);
        }
        runcmd(rcmd->cmd, envp);
    }
    
    exit(0);
}