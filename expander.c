/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 17:10:50 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/20 20:06:14 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>

int     search_dollar(char **s, int i)
{
    while (s[i])
    {
        if (ft_strchr(s[i], '$'))
            return(i);
        i++;
    }
    return (-1);
}

void    expander(t_cmd *tree)
{
    t_pip     *tree1;
    t_redir   *tree2;
    t_exec    *tree3;
    char        **s;
    int       i = 0;

    if (tree->type == PIPE)
    {
        tree1 = (t_pip *)tree;
        expander(tree1->right);
        expander(tree1->left);
    }
    else if (tree->type == REDIR)
    {
        tree2 = (t_redir *)tree;
        expander(tree2->cmd);
    }
    else
    {
        tree3 = (t_exec *)tree;
        i = search_dollar(tree3->argv, i);
        while (i != -1)
        {
            if (ft_strchr((tree3->argv)[i], '?'))
            {
                //check if there is "$?" at the begening and the end
                //split
                s = ft_split((tree3->argv)[i], "$?");
                free((tree3->argv)[i]);
                //join everything again in one string
                //(tree3->argv)[i] = ft_strdup(ft_itoa(GLOBAL));
            }
            //split every
            if (getenv(&((tree3->argv)[i][1])))
            {
                free((tree3->argv)[i]);
                (tree3->argv)[i] = ft_strdup(getenv(&((tree3->argv)[i][1])));
            }
            else
            {
                free((tree3->argv)[i]);
                (tree3->argv)[i] = ft_strdup("");
            }
            i++;
            i = search_dollar(tree3->argv, i);
        }
    }
}