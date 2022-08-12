#include "minishell"
#include "stdio.h"
 
#define EXEC 1
#define REDIR 2
#define PIPE 3

void    parsing_tester(cmd *tree)
{
    pip *tree1;
    redir *tree2;
    exec *tree3;

    if (tree->type == PIPE)
    {
        tree1 = (pip *)tree;
        printf(" | \n");
        parsing_tester(tree->left);
        parsing_tester(tree->right);
    }
    else if (tree->type == REDIR)
    {
        tree2 = (redir *)tree;
        if ()
        printf(" redir \n");
    }
}