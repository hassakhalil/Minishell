/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 20:31:23 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/12 18:48:20 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    free_exec(t_exec *node)
{
    int i = 0;

    while (node->argv[i])
    {
        //debug 
        dprintf(2, "freeing now { %s }\n", node->argv[i]);
        //end debug
        free(node->argv[i]);
        i++;
    }
    //free(node->argv);
    free(node);
}

void    free_redir(t_redir *node)
{

    free(node->file);
    //debug
    dprintf(2, "freed { %s }\n", node->file);
    //end debug
    free(node);
}

void    free_pipe(t_pip *node)
{
    free(node);
}

void    clean(t_cmd *tree)
{
    t_pip     *tree1;
    t_redir   *tree2;
    t_exec    *tree3;

    if (tree->type == PIPE)
    {
        tree1 = (t_pip *)tree;
        clean(tree1->left);
        clean(tree1->right);
        //debug
        dprintf(2, "freeing pipe\n");
        //end debug
        free_pipe(tree1);
    }
    else if (tree->type == REDIR)
    {
        tree2 = (t_redir *)tree;
        clean(tree2->cmd);
        //debug
        dprintf(2, "freeing redir\n");
        //end debug
        free_redir(tree2);
    }
    else
    {
        tree3 = (t_exec *)tree;
        //debug
        dprintf(2, "freeing exec\n");
        //end debuf
        free_exec(tree3);
    }
}