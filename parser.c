/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:44:55 by iakry             #+#    #+#             */
/*   Updated: 2022/10/12 19:43:02 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd* parseredirs(t_cmd *cmd, char **ss, char *es, int flag)
{
    int tok;
    char *q;
    char *eq;
    char    *heredoc;

    while (peek(ss, es, "<>"))
    {
        tok = gettoken(ss, es, 0, 0, flag);
        if (gettoken(ss, es, &q, &eq, flag) != 'a')
        {
            //cleaning should be done here
            if (flag)
            {
                perror("missing file for redirection");
                exit(EXIT_FAILURE);
            }
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
            heredoc = create_heredoc(mkcopy(q, eq));
            cmd = redircmd(cmd, heredoc, O_RDONLY, tok);
            free(heredoc);
            break;
        }
    }
    return cmd;
}

t_cmd* parseexec(char **ss, char *es, t_envvar **env, int flag)
{
    char *q, *eq;
    int tok, argc;
    t_exec *cmd;
    t_cmd *ret;

    ret = execcmd();
    cmd = (t_exec*)ret;
    argc = 0;
    while (peek(ss, es, "<>"))
        ret = parseredirs(ret, ss, es, flag);
    while (!peek(ss, es, "|"))
    {
        tok = gettoken(ss, es, &q, &eq, flag);
        if (tok == 0)
            break;
        while (peek(ss, es, "<>"))
            ret = parseredirs(ret, ss, es, flag);
        if (tok != 'a')
        {
            //cleaning should be done here
            if (flag)
            {
                perror("syntax error");
                exit(EXIT_FAILURE);
            }
        }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
        cmd->argv[argc] = quote_remover(expander(mkcopy(q, eq), *env));
        argc++;
        if(argc >= MAXARGS)
        {
            //cleaning should be done here 
            if (flag)
            {
                perror("Too many args");
                exit(EXIT_FAILURE);
            }
        }
    }
    cmd->argv[argc] = 0;
    return ret;
}

t_cmd* parsepipe(char **ss, char *es, t_envvar **env, int flag)
{
    t_cmd *cmd;
    t_exec *check_empty;
    char    **tt;
    
    cmd = parseexec(ss, es, env, flag);
    if(peek(ss, es, "|"))
    {
        gettoken(ss, es, 0, 0, flag);
        tt = ss;
        check_empty = (t_exec *)cmd;
        if (!check_empty->argv[0] || !empty_cmd(*tt) || complete_pipe(*tt))
        {
            //cleaning should be done here
            if (flag)
            {
                write(2, "syntax error near unexpected token `|'\n", 40);
                exit(58);
            }
        }
        cmd = pipecmd(cmd, parsepipe(ss, es, env, flag));
    }
    return cmd;
}

t_cmd   *parsecmd(char *s, t_envvar **env, int flag)
{
    t_cmd *cmd;
    char *es;

    es = s + ft_strlen(s);
    cmd = parsepipe(&s, es, env, flag);
    peek(&s, es, "");
    if(s != es)
    { 
        if (flag)
        {
            write(2, "Leftovers: ", 12);
            write(2, s, ft_strlen(s));
            exit(EXIT_FAILURE);
        }
    }
    return cmd;
}

