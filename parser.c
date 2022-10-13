/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:44:55 by iakry             #+#    #+#             */
/*   Updated: 2022/10/13 23:56:59 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//add a little expander to remove $ and quote remover 

char    *expand_file(char *arg)
{
    int i = 0;
    char    *new_arg;

    while (arg[i])
    {
        if(arg[i] == '$'&& arg[i + 1] && (arg[i + 1] == '\'' || arg[i + 1] == '\"'))
        {
            new_arg = ft_strjoin3(ft_substr(arg, 0, i), &arg[i + 1]);
            free(arg);
            arg = ft_strdup(new_arg);
            free(new_arg);
        }
        i++;
    }
    return (arg);
}

t_cmd* parseredirs(t_cmd *cmd, char **ss, char *es, int flag, t_envvar **env)
{
    char    *s;
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
            //parse quotes and remove $ before quotes
            cmd = redircmd(cmd, quote_remover(expander(mkcopy(q, eq), *env)), O_RDONLY, tok);
            break;
        }
        else if (tok == '>')
        {
            cmd = redircmd(cmd, quote_remover(expander(mkcopy(q, eq), *env)), O_WRONLY|O_CREAT|O_TRUNC, tok);
            break;
        }
        else if (tok == '+')
        {
            cmd = redircmd(cmd, quote_remover(expander(mkcopy(q, eq), *env)), O_WRONLY|O_CREAT|O_APPEND, tok);
            break;
        }
        else if (tok == '*')
        {
            if (flag)
            {
                //just remove dollar before quotes
                create_heredoc(quote_remover(expand_file(mkcopy(q, eq))));
                s = quote_remover(expand_file(mkcopy(q, eq)));
                heredoc = ft_strjoin("/tmp/", s);
                free(s);
            }
            else
                heredoc = ft_strdup("heredoc");
            cmd = redircmd(cmd, heredoc, O_RDONLY, tok);
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
        ret = parseredirs(ret, ss, es, flag, env);
    while (!peek(ss, es, "|"))
    {
        tok = gettoken(ss, es, &q, &eq, flag);
        if (tok == 0)
            break;
        while (peek(ss, es, "<>"))
            ret = parseredirs(ret, ss, es, flag, env);
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

