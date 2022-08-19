#include "minishell.h"

void    parsing_tester(cmd *result_tree)
{
    pip *tree1;
    redir *tree2;
    exec *tree3;

    if (result_tree->type == '|')
    {
        write (2, "-----|pipe|-----\n", 18);
        tree1 = (pip *)result_tree;
        write (2, "<<<<<<<<-----|pipe left|------\n", 32);
        parsing_tester(tree1->left);
        write (2, "-----|pipe right|----->>>>>>>>\n", 32);
        if (tree1->right->type == ' ')
            write(2, "+++++|last node|+++++\n", 23);
        else if (tree1->right == 0)
            write(2, "(((((((null node)))))))\n", 25);
        parsing_tester(tree1->right);
    }
    else if (result_tree->type == '>')
    {
        write (2, "<><><>|redir|<><><>\n", 21);
        tree2 = (redir *)result_tree;
        parsing_tester(tree2->cmd);
    }
    else
    {
        write (2, "|||-----exec-----|||\n", 22);
        tree3 = (exec *)result_tree;
    } 
}