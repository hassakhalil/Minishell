/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 13:00:15 by hkhalil           #+#    #+#             */
/*   Updated: 2022/08/11 19:58:44 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void errors(char *msg)
{
    printf("%s\n", msg);
    //clean everything
    exit(1);
}

void    executor(void *result_tree)
{
    int p[2];
    int id1;
    int id2;
    cmd *tree_check;
    pip *tree1 == NULL;
    redir *tree2 == NULL;
    exec *tree3 == NULL;

    //cast tree to cmd to access tree->type
    tree_check = (cmd *)result_tree;
    if (tree_check->type == PIPE)
        tree1 = (pip *)result_tree;
    else if (tree_check->type == REDIR)
        tree2 = (redir *)result_tree;
    else if (tree_check->type == EXEC)
        tree3 = (exec *)result_tree;        
    if (tree1)
    {
        if (pipe(p) < 0)
            errors("pipe error");
        id1 = fork();
        if (id1 < 0)
            errors("fork error");
        if (id1 == 0)
        {
            close(1);
            dup(p[1]);
            close(p[0]);
            close(p[1]);
            executor(tree1->left);
        }
        else
        {
            id2 = fork();
            if (id2 < 0)
                errors("fork error");
            if (id2 == 0)
            {
                close(0);
                dup(p[0]);
                close(p[0]);
                close(p[1]);
                executor(tree1->right);
            }
        }
        if (id1 && id2)
        {
            close(p[0]);
            close(p[1]);
            wait();
        }
     }
    else if (tree2)
    {
        //do redir
        executor(/*send next node*/);
    }
    else
    {
        //exec tree3
        execve();
        errors("execve error");
    }       
}