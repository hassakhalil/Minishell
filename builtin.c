/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:02:29 by iakry             #+#    #+#             */
/*   Updated: 2022/10/09 01:14:08 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int valid_name(char *s)
{
    int i = 0;

    if (!ft_isalpha(s[i]))
    {
        dprintf(2, "invalid name\n");
        return(0);
    }
    while (s[i])
    {
        if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
        {
                    dprintf(2, "invalid name\n");
            return (0);
        }
        i++;
    }
    return (1);
}

void    add_local(t_exec *cmd, t_envvar **local)
{
    int i = 0;
    //check if its already there
    t_envvar    *addr = *local;

   
    while (cmd->argv[i])
    { 
        char **v = ft_split(cmd->argv[i], '=');
        if (v && v[0] && v[1] && valid_name(v[0]))
        {
            if (if_exist_add(&addr, v, 1));
            else
            {
                addr = *local; 
                ft_lstadd_back(local, ft_lstadd_new(v[0], v[1]));
            }
        }
        //free
        i++;
    }
}

int builtin(char *buff, t_envvar **env, t_envvar **local)
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
        else if (!ft_strcmp(cmd->argv[0], "cd"))
        {
            ft_cd(cmd, *env);
            return (1);
        }
        else if (ft_strchr(cmd->argv[0],'='))
        {
            
           add_local(cmd, local);
           return(1);
        }
        else if (!ft_strcmp(cmd->argv[0], "unset"))
        {
           ft_unset(cmd, env);
           return (1);
        }
        else if (!ft_strcmp(cmd->argv[0], "export"))
        {
           ft_export(cmd, env, local);
           return (1);
        }
    }
    //add unset and export here
    //clear 
    return (0);
}

//exit

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


//env

int ft_check_for_env(char *s)
{
    if (ft_strlen(s) != 3)
        return(0);
    if (ft_tolower(s[0]) == 'e' && ft_tolower(s[1]) == 'n' && ft_tolower(s[2]) == 'v')
        return(1);
    return (0);
}

void ft_env(t_exec *cmd, t_envvar *env)
{
    if (cmd->argv[1])
    {
        printf("env: %s: No such file or directory\n", cmd->argv[1]);
        exit(127);
    } 
    else
    {
        while (env)
        {
            printf("%s=%s\n", env->name, env->value);
            env = env->next;
        }
    }
    exit(0);
}

//pwd

int ft_check_for_pwd(char *s)
{
    if (ft_strlen(s) != 3)
        return(0);
    if (ft_tolower(s[0]) == 'p' && ft_tolower(s[1]) == 'w' && ft_tolower(s[2]) == 'd')
        return(1);
    return (0);
}

void ft_pwd(void)
{
    char cwd[100];

    if (getcwd(cwd, 100))
        printf("%s\n", cwd);
    exit(0);
}

//cd

void ft_cd(t_exec *cmd, t_envvar *env)
{
    if (cmd->argv[1])
        if (chdir(cmd->argv[1]))
        {
            write(2, "cd: ",5);
            perror(cmd->argv[1]);
            GLOBAL = 1;
            return ;
        }
    if (!(cmd->argv[1]))
        while (env)
        {
            if (!ft_strcmp(env->name, "HOME"))
                chdir(env->value);
            env = env->next;
        }
        GLOBAL = 0;
}

//export

char **if_exist_add(t_envvar **env, char **s, int   flag)
{
    char    **v= malloc(sizeof(char *) *3);

    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
    while ( env && *env)
    {
        if (!ft_strcmp((*env)->name, s[0]))
        {
            v = malloc(sizeof(char *) *3);
            v[0] = ft_strdup((*env)->name);
            if (flag)
            {
                if (s[1])
                {
                    (*env)->value = ft_strdup(s[1]);
                    v[1] = ft_strdup((*env)->value);
                }
                else
                    v[1] = 0;
            }
            else
                v[1] = ft_strdup((*env)->value);
            v[2]=0;
            return (v);
        }
        (*env) = (*env)->next;
    }
    return (0);
}

void ft_export(t_exec *cmd, t_envvar **env, t_envvar **local)
{
    int i = 1;
    char    **v;
    char    **tmp = NULL;
    t_envvar    *tmp_local;
    t_envvar    *addr;
    t_envvar    *local_addr;
    
    addr = *env;
    local_addr = *local;
    while (cmd->argv[i])
    {
       
        v = ft_split(cmd->argv[i], '=');
        if (ft_strchr(cmd->argv[i], '='))
        {
            if (if_exist_add(&addr, v, 1));
            else  if (valid_name(v[0]))
                ft_lstadd_back(env, ft_lstadd_new(v[0], v[1])); 
        }
        else
        {   
            tmp_local = *local;
            tmp = if_exist_add(&tmp_local, &cmd->argv[i], 0);
            if(if_exist_add(&addr, tmp, 1));
            else if (tmp && tmp[1])
                ft_lstadd_back(env, ft_lstadd_new(tmp[0], tmp[1]));
        }
        i++;
    }
}

//unset


char *if_exist_delete(t_envvar **env, char *s)
{
    t_envvar    *tmp;
    t_envvar    *prev;
    t_envvar    *next;
    t_envvar    *list;
    int         i = 0;
    int         n = ft_lstsize(*env);

    prev = *env;
    list = *env;
    while (list)
    {
        tmp= list;
        if (!ft_strcmp(list->name, s))
        {
            if (i == 0)
            {
                tmp = list;
                env = &(tmp->next);
                free(tmp->name);
                free(tmp->value);
                free(tmp);
            }
            else if (i + 1 == n)
            {
                tmp = list;
                free(tmp->name);
                free(tmp->value);
                free(tmp);
                prev->next = NULL;
            }
            else
            {
                tmp = list;
                next = tmp->next;
                free(tmp->name);
                free(tmp->value);
                free(tmp);
                prev->next=next;
            }
            break;
        }
        prev = list;
        list = list->next;
        i++;
    }
    return (0);
}

void ft_unset(t_exec *cmd, t_envvar **env)
{
    int i = 1;

    while (cmd->argv[i])
    {
        if_exist_delete(env, cmd->argv[i]);
        i++;
    }
}

//echo

int ft_check_for_echo(char *s)
{
    if (ft_strlen(s) != 4)
        return(0);
    if (ft_tolower(s[0]) == 'e' && ft_tolower(s[1]) == 'c' && ft_tolower(s[2]) == 'h' && ft_tolower(s[3]) == 'o')
        return(1);
    return (0);
}

int options(char *s)
{
    int i = 0;

    if (s[i] != '-')
        return(0);
    i++;
    while (s[i])
    {
        if (s[i] != 'n')
            return (0);
        i++;
    }
    return (1);
    
}

void ft_echo(t_exec *cmd)
{
    int i = 1;
    int noption = 0;

    if (cmd->argv[i])
    {
        while (options(cmd->argv[i]))
        {
            noption = 1;
            i++;
        }
        while (cmd->argv[i])
        {
            printf("%s", cmd->argv[i]);
            i++;
            if (cmd->argv[i])
                printf(" ");
        }
    }
    if (noption == 0)
        printf("\n");
    exit(0);
}
