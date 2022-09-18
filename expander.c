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

void    expander(t_cmd *tree, t_env *env)
{
    t_pip     *tree1;
    t_redir   *tree2;
    t_exec    *tree3;

    if (tree->type == PIPE)
    {
        tree1 = (t_pip *)tree;
        expander(tree1->right, env);
        expander(tree1->left, env);
    }
    else if (ree->type == REDIR)
    {
        tree2 = (t_redir *)tree;
        expander(tree2->cmd, env);
    }
    else
    {
        while (/*there is a $x in argv[MAXAERGS]*/)
        {
            if (/* x == '?'*/)
                //replace $x with GLOBAL value
            else if (//search for x in env)
                //replace $x with path[i];
        }
    }
}