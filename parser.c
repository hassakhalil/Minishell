/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:44:55 by iakry             #+#    #+#             */
/*   Updated: 2022/09/20 23:40:59 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd* parseredirs(t_cmd *cmd, char **ss, char *es)
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
            cmd = redircmd(cmd, mkcopy(q, eq), O_WRONLY|O_CREAT|O_TRUNC, tok);
            break;
        }
        if (tok == '+')
        {
            cmd = redircmd(cmd, mkcopy(q, eq), O_WRONLY|O_CREAT|O_APPEND, tok);
            break;
        }
        if (tok == '*')
        {
            //here doc here
            cmd = redircmd(cmd, create_heredoc(mkcopy(q, eq)), O_RDONLY, tok);
            break;
        }
    }
    return cmd;
}

t_cmd* parseexec(char **ss, char *es)
{
    char *q, *eq;
    int tok, argc;
    t_exec *cmd;
    t_cmd *ret;

    ret = execcmd();
    cmd = (t_exec*)ret;
    argc = 0;
    while (peek(ss, es, "<>"))
        ret = parseredirs(ret, ss, es);
    while (!peek(ss, es, "|"))
    {
        tok = gettoken(ss, es, &q, &eq);
        if (tok == 0)
            break;
        while (peek(ss, es, "<>"))
            ret = parseredirs(ret, ss, es);
        if (tok != 'a')
        {
            perror("syntax error");
            exit(EXIT_FAILURE);
        }
        //add expander here                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
        cmd->argv[argc] = expander(ft_strdup(mkcopy(q, eq)));
        argc++;
        if(argc >= MAXARGS)
        {
            perror("Too many args");
            exit(EXIT_FAILURE);
        }
    }
    cmd->argv[argc] = 0;
    return ret;
}

t_cmd* parsepipe(char **ss, char *es)
{
    t_cmd *cmd;
    
    cmd = parseexec(ss, es);
    if(peek(ss, es, "|"))
    {
        gettoken(ss, es, 0, 0);
            cmd = pipecmd(cmd, parsepipe(ss, es));
    }
    return cmd;
}

t_cmd   *parsecmd(char *s)
{
    t_cmd *cmd;
    char *es;

    es = s + ft_strlen(s);
    cmd = parsepipe(&s, es);
    peek(&s, es, "");
    if(s != es)
    {
        write(2, "Leftovers: ", 12);
        write(2, s, ft_strlen(s));
        exit(EXIT_FAILURE);
    }
    return cmd;
}

