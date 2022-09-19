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
#include <errno.h>
int     search_dollar(char **s, int i)
{
    //return place where you found it or 0 if you dont
    while (s[i])
    {
        if (ft_strchr(s[i], '$'))
        {
            //dprintf(2, "found dollaaaaaaaaar$$$$$$\n");
            return(i);
        }
        i++;
    }
    return (-1);
}

void    expander(t_cmd *tree)
{
    t_pip     *tree1;
    t_redir   *tree2;
    t_exec    *tree3;
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
            if (!strcmp((tree3->argv)[i], "$?"))
            {
                free((tree3->argv)[i]);
                (tree3->argv)[i] = ft_strdup(ft_itoa(GLOBAL));
            }
            //
            dprintf(2, "%s\n", &((tree3->argv)[i][1]));
                
            char *l =     ft_strdup("LOGNAME");
            dprintf(2, "%s\n", getenv(l));
            dprintf(2, "%s\n", strerror(errno));
            //
            if (getenv(&((tree3->argv)[i][1])))
            {
                    free((tree3->argv)[i]);
                    (tree3->argv)[i] = ft_strdup(getenv(&((tree3->argv)[i][1])));
            }
            i++;
            i = search_dollar(tree3->argv, i);
        }
    }
}