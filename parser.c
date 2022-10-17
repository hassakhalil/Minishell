/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 11:44:55 by iakry             #+#    #+#             */
/*   Updated: 2022/10/17 07:46:52 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_cmd* parseredirs(t_cmd *cmd, char **ss, char *es, t_envvar **env)
{
    char    *s;
    int tok;
    char *q;
    char *eq;
    char    *heredoc;


    tok = gettoken(ss, es, 0, 0);
    if (gettoken(ss, es, &q, &eq) != 'a')
		errors(NULL, 20);
    if (tok == '<')
        cmd = redircmd(cmd, quote_remover(expander(mkcopy(q, eq), *env)), O_RDONLY, tok);
    else if (tok == '>')
        cmd = redircmd(cmd, quote_remover(expander(mkcopy(q, eq), *env)), O_WRONLY|O_CREAT|O_TRUNC, tok);
    else if (tok == '+')
        cmd = redircmd(cmd, quote_remover(expander(mkcopy(q, eq), *env)), O_WRONLY|O_CREAT|O_APPEND, tok);
    else if (tok == '*')
    {
        if (g_var == -100)
            create_heredoc(quote_remover(expand_file(mkcopy(q, eq))));
        s = quote_remover(expand_file(mkcopy(q, eq)));
        heredoc = ft_strjoin("/tmp/", s);
        free(s);
        cmd = redircmd(cmd, heredoc, O_RDONLY, tok);
    }
    return cmd;
}

t_cmd* parseexec(char **ss, char *es, t_envvar **env)
{
    char *q, *eq;
    int tok, argc;
    t_exec *cmd;
    t_cmd *ret;

    ret = execcmd();
    cmd = (t_exec*)ret;
    argc = 0;
    while (peek(ss, es, "<>"))
        ret = parseredirs(ret, ss, es, env);
    while (!peek(ss, es, "|"))
    {
        tok = gettoken(ss, es, &q, &eq);
        if (tok == 0)
            break;
        while (peek(ss, es, "<>"))
            ret = parseredirs(ret, ss, es, env);
        if (tok != 'a')
			errors(NULL, 21);
        cmd->argv[argc] = quote_remover(expander(mkcopy(q, eq), *env));
        argc++;
        if(argc >= MAXARGS)
			errors(NULL, 22);
    }
    cmd->argv[argc] = 0;
    return ret;
}

t_cmd* parsepipe(char **ss, char *es, t_envvar **env)
{
    t_cmd *cmd;
    t_exec *check_empty;
    char    **tt;
    
    cmd = parseexec(ss, es, env);
    if(peek(ss, es, "|"))
    {
        gettoken(ss, es, 0, 0);
        tt = ss;
        check_empty = (t_exec *)cmd;
        if (!check_empty->argv[0] || !empty_cmd(*tt) || complete_pipe(*tt))
			errors(NULL, 23);
        cmd = pipecmd(cmd, parsepipe(ss, es, env));
    }
    return cmd;
}

t_cmd   *parsecmd(char *s, t_envvar **env)
{
    t_cmd *cmd;
    char *es;

    es = s + ft_strlen(s);
    cmd = parsepipe(&s, es, env);
    peek(&s, es, "");
    if(s != es)
		errors(s, 24);
    return cmd;
}

