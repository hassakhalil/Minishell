/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 07:14:38 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 07:37:25 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int if_exist_add(t_envvar **env, char **s, int flag)
{
    while (env && *env)
    {
        if (!ft_strcmp((*env)->name, s[0]))
        {
            if (flag && s[1])
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
}

void ft_export(t_exec *cmd, t_envvar **env)
{
    int i = 1;
    char    **v;
    t_envvar    *addr;

    if (!cmd->argv[i])
        export_noargs(env);
    while (cmd->argv[i])
    {
        addr = *env;
        if (ft_strchr(cmd->argv[i], '='))
        {
            v = ft_split(cmd->argv[i], '=');
            if (!v[1])
            {
                v[1] = ft_strdup("");
            }
            if (if_exist_add(&addr, v, 1));
            else
            { 
                if (valid_name(v[0]))
                {
                    //better to give ft_strdup
                    ft_lstadd_back(env, ft_lstadd_new(v[0], v[1]));
                }
                else
                {  
                    GLOBAL = -2;
                    printf("export: `%s': not a valid identifier\n", cmd->argv[i]);
                }  
            }
        }
        else
        {
            if (if_exist_add(&addr, &cmd->argv[i], 0));
            else if (valid_name(cmd->argv[i]))
                ft_lstadd_back(env, ft_lstadd_new(ft_strdup(cmd->argv[i]), NULL));
            else
            {  
                GLOBAL = -2;
                printf("export: `%s': not a valid identifier\n", cmd->argv[i]);
            }
        }
        i++;
    }
}