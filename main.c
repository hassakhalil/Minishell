/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/08/25 02:57:16 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *getcmd()
{
    char *buff;

    if (isatty(fileno(stdin)))
        buff = readline("$ ");
    if (buff)
        return buff;
    return NULL;
}

struct cmd* parsecmd(char *s)
{
    struct cmd *cmd;
    char *es;

    es = s + ft_strlen(s);
    cmd = parseline(&s, es);
    peek(&s, es, "");
    if(s != es)
    {
        err_putchar("Leftovers: ");
        err_putchar(s);
        exit(EXIT_FAILURE);
    }
    return cmd;
}

int is_alpha(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
        return 1;
    return 0;
}

int main(int ac, char **av, char **env)
{
    static char *buff;
    static char **var;
    struct env *envp;

    system("clear");
    envp = envpath(env);
    while ((buff = getcmd()))
    {
        if (buff && *buff)
            add_history(buff);
        if (!cd(buff))
            continue;
        if (!strcmp(buff, "exit"))
            exit(0);
        if (forkk() == 0)
            executor(parsecmd(buff), envp);
        wait(0);
    }
    return(0);
}
