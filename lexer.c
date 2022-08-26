/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 15:26:58 by iakry             #+#    #+#             */
/*   Updated: 2022/08/26 21:37:30 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct cmd* parseredirs(struct cmd *cmd, char **ss, char *es)
{
    int tok;
    char *q;
    char *eq;

    while (peek(ss, es, "<>"))
    {
        tok = gettoken(ss, es, 0, 0);
        if (gettoken(ss, es, &q, &eq) != 'a')
        {
            perror("missing file for redirection");
            exit(EXIT_FAILURE);
        }
        if (tok == '<')
        {
            cmd = redircmd(cmd, mkcopy(q, eq), O_RDONLY, tok);
            break;
        }
        if (tok == '>')
        {
            write(2, "we got redirection here\n", 25);
            cmd = redircmd(cmd, mkcopy(q, eq), O_WRONLY|O_CREAT|O_TRUNC, tok);
            break;
        }
        if (tok == '+')
        {
            cmd = redircmd(cmd, mkcopy(q, eq), O_WRONLY|O_CREAT, tok);
            break;
        }
    }
    return cmd;
}

struct cmd* parseblock(char **ss, char *es)
{
    struct cmd *cmd;
    
    if (!peek(ss, es, "("))
    {
        perror("parseblock");
        exit(EXIT_FAILURE);
    }
    gettoken(ss, es, 0, 0);
    cmd = parseline(ss, es);
    if (!peek(ss, es, ")"))
    {
        perror("syntax - missing ) ");
        exit(EXIT_FAILURE);
    }
    gettoken(ss, es, 0, 0);
    cmd = parseredirs(cmd, ss, es);
    return cmd;
}

struct cmd* parseexec(char **ss, char *es)
{
    char *q, *eq;
    int tok, argc;
    struct execcmd *cmd;
    struct cmd *ret;
    
    if (peek(ss, es, "("))
        return (parseblock(ss, es));

    ret = execcmd();
    cmd = (struct execcmd*)ret;
    
    argc = 0;
    //ret = parseredirs(ret, ss, es);
    while (!peek(ss, es, "|"))
    {
        ret = parseredirs(ret, ss, es);
        tok = gettoken(ss, es, &q, &eq);
        if (tok == 0)
            break;
        if (tok != 'a')
        {
            perror("syntax error");
            exit(EXIT_FAILURE);
        }
        cmd->argv[argc] = mkcopy(q, eq);
        argc++;
        if(argc >= MAXARGS)
        {
            perror("Too many args");
            exit(EXIT_FAILURE);
        }
        ret = parseredirs(ret, ss, es);
    }
    cmd->argv[argc] = 0;
    return ret;
}

struct cmd* parsepipe(char **ss, char *es)
{
    struct cmd *cmd;
    char *pipeerr;
    
    cmd = parseexec(ss, es);
    if(peek(ss, es, "|"))
    {
        gettoken(ss, es, 0, 0);
            cmd = pipecmd(cmd, parsepipe(ss, es));
    }
    return cmd;
}

struct cmd* parseline(char **ss, char *es)
{
    struct cmd *cmd;
    
    cmd = parsepipe(ss, es);
    while (peek(ss, es, "&"))
        gettoken(ss, es, 0, 0);
    return cmd;
}
