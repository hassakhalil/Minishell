/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 13:02:29 by iakry             #+#    #+#             */
/*   Updated: 2022/10/04 23:32:23 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}


int builtin(char *buff, t_envvar *env)
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
            ft_cd(cmd, env);
            return (1);
        }
    }
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

void ft_env(t_exec *cmd, t_envvar *var)
{
    if (cmd->argv[1])
    {
        printf("env: %s: No such file or directory\n", cmd->argv[1]);
        exit(127);
    } 
    else
        while (var)
        {
            printf("%s=%s\n", var->name, var->value);
            var = var->next;
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
}*/

void ft_export(t_exec *cmd, t_envvar *env)
{
    //check the name (syntax)if its not valid display error
    //check if its already there if yes replace it with the new value (if there is no value do nothing)
    //else check local if you find it ->export
    //create it

    //char **p;
    ///if (!ft_strcmp(cmd->argv[0], "export"))
       // if (cherche(cmd->argv[1], "="))
        //{
          //  p = ft_split(cmd->argv[1], '=');
            //if (!if_varexist(env, p))
              //  ft_lstadd_back(&env, ft_lstadd_new(p[0], p[1]));
        //}
    //exit(?)
    return ;
}

void ft_unset(t_exec *cmd, t_envvar *env)
{
    //unset alone does nothing
    //check every variable if it exist remove it else diplay  error
    //ft_list_remove_if(&env, cmd->argv[1], ft_strcmp);
    //exit(?)
     return ;
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

/*int if_localexist(t_localvar *local, char **s)
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
}*/
