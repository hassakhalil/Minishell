/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:20:10 by iakry             #+#    #+#             */
/*   Updated: 2022/08/24 01:05:04 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define COUNT 10

char *getcmd()
{
    char *buff;
    char cwd[100];
    char str[100] = "\033[1;31m➜\033[0;34m";

    getcwd(cwd, 100);
    if (isatty(fileno(stdin)))
        buff = readline(strcat(strcat(str, cwd), "\033[0m"));
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
    //signal(SIGINT, handle_sig);
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

// char **variable(char *buff, char **var){
//     int i  = 0;
//     char *s = buff;

//     while (s[i])
//         if (is_alpha(s[i]) && s[i+1] = '=')
//             break;
//     while (is_alpha(s[i]))
//         i--;
//     while (s[i])
//     {
//         var = 
//     }
// }

// void builtins(static char *buff)
// {
//     if ()
// }

// void	signals(void)
// {
// 	signal(SIGQUIT, SIG_IGN);
// 	signal(SIGINT, handle_sig);
// }

int main(int ac, char **av, char **env)
{
    static char *buff;
    static char **var;
    struct env *envp;

    system("clear");
    //printheader();
    //signals();
    envp = envpath(env);
    while ((buff = getcmd()))
    {
        //variable(buff, var);
        if (buff && *buff)
            add_history(buff);
        if (!cd(buff))
            continue;
        if (!strcmp(buff, "exit"))
            exit(0);
        if (forkk() == 0)
        {
            //runcmd((parsecmd(buff)), envp);
            //int flag = 0;
            //int backup = dup(1);
            parsing_tester(parsecmd(buff));
        }
        wait(0);
    }
    return(0);
}
