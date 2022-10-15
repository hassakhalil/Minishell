/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:02:29 by iakry             #+#    #+#             */
/*   Updated: 2022/10/15 05:42:37 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin(char *buff, t_envvar **env)
{
    t_cmd   *tree;
    t_exec  *cmd;
    
    tree = parsecmd(buff, env, 0);
    if (tree->type == EXEC)
    {
        cmd = (t_exec *)tree;
        if (!ft_strcmp(cmd->argv[0], "exit"))
        {
            ft_exit(cmd);
            clean(tree);
            return (1);
        }
        else if (!ft_strcmp(cmd->argv[0], "cd"))
        {
            ft_cd(cmd, *env);
            clean(tree);
            return (1);
        }
        else if (!ft_strcmp(cmd->argv[0], "unset"))
        {
           ft_unset(cmd, env);
           if (GLOBAL == -2)
                GLOBAL = 1;
           else
                GLOBAL = 0;
            clean(tree);
           return (1);
        }
        else if (!ft_strcmp(cmd->argv[0], "export"))
        {
           ft_export(cmd, env);
           if (GLOBAL == -2)
                GLOBAL = 1;
           else
                GLOBAL = 0;
            clean(tree);
           return (1);
        }
    }
    clean(tree);
    return (0);
}

void    executor_builtin(t_exec *tree3, t_envvar **env_list)
{
    if (!empty_cmd(tree3->argv[0]))
        exit(0);
    if (!ft_strcmp(tree3->argv[0], "exit"))
    {
        ft_exit(tree3);
        exit(GLOBAL);
    }
    else if (!ft_strcmp(tree3->argv[0], "cd"))
    {
        ft_cd(tree3, *env_list);
        if (errno == 13 || errno == 2)
            exit(1);
        exit(0);
    }
    else if (ft_check_for_pwd(tree3->argv[0]))
        ft_pwd();
    else if (ft_check_for_echo(tree3->argv[0]))
        ft_echo(tree3);
    else if (ft_check_for_env(tree3->argv[0]))
        ft_env(tree3, *env_list);
    else if (!ft_strcmp(tree3->argv[0], "export"))
    {
        ft_export(tree3, env_list);
        if (GLOBAL == -2)
            exit(1);
        exit(0);
    }
    else if (!ft_strcmp(tree3->argv[0], "unset"))
    {
        ft_unset(tree3, env_list);
        if (GLOBAL == -2)
            exit(1);
        exit (0);
    }
}

//export

int if_exist_add(t_envvar **env, char **s)
{
    while (env && *env)
    {
        if (!ft_strcmp((*env)->name, s[0]))
        {
            if (s[1])
                (*env)->value = ft_strdup(s[1]);
            return (1);
        }
        (*env) = (*env)->next;
    }
    return (0);
}

void    export_noargs(t_envvar  **env)
{
    t_envvar    *tmp;
    char        **min;
    char        *c;
    int         n = 0;

    if (!env && !(*env))
        return ;
    c = ft_strdup("");
    tmp = *env;
    min = malloc(sizeof(char *) * 2);
    min[0] = ft_strdup(tmp->name);
    min[1] = ft_strdup(tmp->value);
    n = ft_lstsize(tmp);
    while (n)
    {
        tmp = *env;
        while (tmp)
        {
            if (ft_strcmp(tmp->name, c) > 0)
            {
                //free(min[0]);
                //free(min[1]);
                min[0] = ft_strdup(tmp->name);
                min[1] = ft_strdup(tmp->value);
                break;
            }
            tmp = tmp->next;
        }
        tmp = *env;
        while (tmp)
        {
            if ((ft_strcmp(min[0], tmp->name) > 0) && (ft_strcmp(tmp->name, c) > 0))
            {
                //free(min[0]);
                //free(min[1]);
                min[0] = ft_strdup(tmp->name);
                min[1] = ft_strdup(tmp->value);
            }
            tmp = tmp->next;
        }
        if(min[1])
            printf("declare -x %s=\"%s\"\n", min[0], min[1]);
        else
            printf("declare -x %s\n", min[0]);
        free(c);
        c = ft_strdup(min[0]);
        n--;
    }
    //free(min[0]);
    //free(min[1]);
    //free(c);
    //free(min);
}

void ft_export(t_exec *cmd, t_envvar **env)
{
    int i = 1;
    char    **v;
    char    **tmp;
    t_envvar    *addr;

    if (!cmd->argv[i])
        export_noargs(env);
    while (cmd->argv[i])
    {
        addr = *env;
        v = ft_split(cmd->argv[i], '=');
        tmp = malloc(sizeof(char *) * 2);
        tmp[0] = ft_strdup(cmd->argv[i]);
        tmp[1] = 0;
        if (ft_strchr(cmd->argv[i], '='))
        {
            if (!v[1])
            {
                //free(v[1]);
                v[1] = ft_strdup("");
            }
            if (if_exist_add(&addr, v))
            {
                //free(v[0]);
                //free(v[1]);
                ;
            }
            else
            { 
                if (valid_name(v[0]))
                    ft_lstadd_back(env, ft_lstadd_new(v[0], v[1]));
                else
                {  
                    GLOBAL = -2;
                    printf("export: `%s': not a valid identifier\n", cmd->argv[i]);
                    //free(v[0]);
                    //free(v[1]);
                }  
            }
            //free(v);
            //free(tmp[0]);
            //free(tmp[1]);
            //free(tmp);
        }
        else
        {
            if (if_exist_add(&addr, tmp));
            else if (valid_name(cmd->argv[i]))
                ft_lstadd_back(env, ft_lstadd_new(cmd->argv[i], NULL));
            else
            {  
                GLOBAL = -2;
                printf("export: `%s': not a valid identifier\n", cmd->argv[i]);
            }
            //free(v[0]);
            //free(v[1]);
            //free(v);
            //free(tmp[0]);
           // free(tmp[1]);
            //free(tmp);
        }
        i++;
    }
}

