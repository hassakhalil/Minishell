/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:02:29 by iakry             #+#    #+#             */
/*   Updated: 2022/10/03 22:35:07 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin(char *buff)
{
    t_cmd   *tree;
    t_exec  *cmd;

    tree = parsecmd(buff);
    if (tree->type == EXEC)
    {
        cmd = (t_exec *)tree;
        if (!ft_strcmp(cmd->argv[0], "exit"))
        {
            ft_exit(cmd);
            return (1);
        }
        /*else if (!ft_strcmp(cmd->argv[0], "cd"))
        {
        }*/
    }
    //clear 
    return (0);
}

/*int ft_isallnum(char *s)
{
    while (*s)
        if (!ft_isdigit(*s++))
            return 0;
    return 1;
}*/

/*void ft_clear()
{
    printf("\e[1;1H\e[2J");
}*/

void ft_exit(t_exec *node)
{
    int      i = 0;
    int      k = 0;

    while (node->argv[k])
        k++;
    if (node->argv[1])
    {
        i = 0;
        while (node->argv[1][i])
        {
            if (!ft_isdigit(node->argv[1][i]))
            {
                write(2, "exit: ", 7);
                write(2, node->argv[1], ft_strlen(node->argv[1]));
                write(2, ": numeric argument required\n", 29);
                exit(255);
            }
            i++;
        }
        if (k > 2)
        {
            write(2, "exit: too many arguments\n", 26);
            GLOBAL = 1;
            //clean everything
            return ;
        }
        exit(ft_atoi(node->argv[1]));
    }
    exit(GLOBAL);
}

/*void ft_env(t_exec *cmd, t_envvar *var)
{
    if (cmd->argv[1])
        printf("env: %s: No such file or directory\n", cmd->argv[1]);
    else
        while (var)
        {
            printf("%s=%s\n", var->name, var->value);
            var = var->next;
        }
}

void ft_pwd(void)
{
    char cwd[100];
    
    getcwd(cwd, 100);
    printf("%s\n", cwd);
}

int builtin_expander(char *buff, t_envvar *env, t_localvar **local)
{
    int i = 0;
    char *s;
    (void)local;
    if (buff[i] == '$')
    {
        i++;
        while (buff[i] && !is_space(buff[i]))
            i++;
        printf("expander\n");
        s = ft_substr(buff, 1, i);
        while (env){
            if (!ft_strcmp(env->name, s))
                printf("%s", env->value);
            env = env->next;
        }
    }
    return i;
}*/

/*void ft_cd(t_exec *cmd, t_ *env)
{
    if (!ft_strcmp(cmd->argv[0], "cd") && cmd->argv[1])
        if (chdir(cmd->argv[1]))
            perror("cd");
    if (!ft_strcmp(cmd->argv[0], "cd") && !(cmd->argv[1]))
        while (env)
        {
            if (!ft_strcmp(env->name, "HOME"))
                chdir(env->value);
            env = env->next;
        }
}*/

/*int if_varexist(t_envvar *env, char **s)
{
    while (env)
    {
        if (!ft_strcmp(env->name, s[0]))
        {
            env->value = s[1];
            return 1;
        }
        env = env->next;
    }
    return 0;
}

void ft_export(t_exec *cmd, t_envvar *env)
{
    char **p;

    if (!ft_strcmp(cmd->argv[0], "export"))
        if (cherche(cmd->argv[1], "="))
        {
            p = ft_split(cmd->argv[1], '=');
            if (!if_varexist(env, p))
                ft_lstadd_back(&env, ft_lstadd_new(p[0], p[1]));
        }
}

void ft_unset(t_exec *cmd, t_envvar *env)
{
    ft_list_remove_if(&env, cmd->argv[1], ft_strcmp);
}

int echo_checker(char *s)
{
    int i = 0;

    if (s[i] && s[i] == '-')
        i++;
    while (s[i] && s[i] == 'n')
        i++;
    if (s[i])
        return 0;
    return 1;
}

void ft_echo(t_exec *cmd, t_envvar *env, t_localvar *local)
{
    int i = 0;

    if (cherche(cmd->argv[++i], "-n"))
    {
        while (cherche(cmd->argv[i], "-n"))
        {
            if (!echo_checker(cmd->argv[i]))
                break;
            i++;
        }
        while (cmd->argv[i])
        {
            i += builtin_expander(cmd->argv[i], env, &local);
            printf("%s", cmd->argv[i++]);
            if (cmd->argv[i])
                printf(" ");
        }
    }
    else 
    {
        while (cmd->argv[i])
        {
            if (cherche(cmd->argv[i], "$"))
                printf("---- %s ----\n", cmd->argv[i]);
                //builtin_expander(cmd->argv[i++], env, &local);
            if (cmd->argv[i])
                printf("%s", cmd->argv[i++]);
            if (cmd->argv[i])
                printf(" ");
            else
                printf("\n");
        }
    }
}

int cherche(char *s, char *f)
{
    int i = -1;
    int j = 0;

    while (s[++i])
    {
        j = 0;
        while (s[i+j] == f[j])
        {
            j++;
            if (!f[j])
                return 1;
        }
    }
    return 0;
}

int if_localexist(t_localvar *local, char **s)
{
    while (local)
    {
        if (!ft_strcmp(local->name, s[0]))
        {
            local->value = s[1];
            return 1;
        }
        local = local->next;
    }
    return 0;
}

void ft_localvar(t_exec *cmd, t_localvar *local)
{
    char **p;

    if (cherche(cmd->argv[0], "="))
    {
        p = ft_split(cmd->argv[0], '=');
        if (!if_localexist(local, p))
            ft_lstadd_localback(&local, ft_lstadd_localnew(p[0], p[1]));
        while (local)
        {
            printf("%s = %s\n",local->name, local->value);
            local = local->next;
        }
    }
}

void scan_and_run(t_exec *cmd, t_envvar *env, t_localvar *local)
{
    if (cherche(cmd->argv[0], "cd"))
        ft_cd(cmd, env);
    if (cherche(cmd->argv[0], "pwd"))
        ft_pwd(cmd);
    if (cherche(cmd->argv[0], "echo"))
        ft_echo(cmd, env, local);
    if (cherche(cmd->argv[0], "exit"))
        ft_exit(cmd);
    if (cherche(cmd->argv[0], "env"))
        ft_env(cmd, env);
    if (cherche(cmd->argv[0], "export"))
        ft_export(cmd, env);
    if (cherche(cmd->argv[0], "unset"))
        ft_unset(cmd, env);
    if (cherche(cmd->argv[0], "clear"))
        ft_clear();
    if (cherche(cmd->argv[0], "="))
        ft_localvar(cmd, local);
}

void builtin(t_cmd *tree, t_envvar *env, t_localvar *local)
{
    t_exec *cmd = (t_exec *)tree;

    scan_and_run(cmd, env, local);
}*/