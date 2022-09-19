/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:10:50 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/17 17:30:43 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     search_dollar(char **s)
{
    int i = 1;
    //return place where you found it or 0 if you dont
    while (s[i])
    {
        if (ft_strchr(s[i], '$'))
        {
            dprintf(2, "found dollaaaaaaaaar$$$$$$\n");
            return(i);
        }
        i++;
    }
    return(0);
}

int     search_table(char **s, char *c)
{
    int i = 1;
    //return place where you found it or 0 if you dont
    while (s[i])
    {
        if (!strcmp(s[i], c))
            return(i);
        i++;
    }
    return (0);
}

void    expander(t_cmd *tree, t_env *env)
{
    t_pip     *tree1;
    t_redir   *tree2;
    t_exec    *tree3;
    int       i;
    int       j;
    int       k;

    if (tree->type == PIPE)
    {
        tree1 = (t_pip *)tree;
        expander(tree1->right, env);
        expander(tree1->left, env);
    }
    else if (tree->type == REDIR)
    {
        tree2 = (t_redir *)tree;
        expander(tree2->cmd, env);
    }
    else
    {
        tree3 = (t_exec *)tree;
        i = search_dollar(tree3->argv);
        while (i)
        {
            if (!strcmp((tree3->argv)[i], "$?"))
            {
                free((tree3->argv)[i]);
                (tree3->argv)[i] = ft_strdup(ft_itoa(GLOBAL));
            }
            else
            {
                j = search_table(env->path, &(tree3->argv)[i][1]);
                if (j)
                {
                    free((tree3->argv)[i]);
                    k = 0;
                    while((env->path)[j][k] != '=')
                    k++;
                    (tree3->argv)[i] = ft_strdup(&(env->path)[j][++k]);
                }
                i = search_dollar(tree3->argv);
            }
        }
    }
}