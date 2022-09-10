#include "minishell.h"

void    parsing_tester(cmd *result_tree)
{
    t_pip *tree1;
    t_redir *tree2;
    t_exec *tree3;

    if (result_tree->type == PIPE)
    {
        write (2, "-----|pipe|-----\n", 18);
        tree1 = (t_pip *)result_tree;
        write (2, "<<<<<<<<-----|pipe left|------\n", 32);
        parsing_tester(tree1->left);
        write (2, "-----|pipe right|----->>>>>>>>\n", 32);
        if (tree1->right->type == ' ')
            write(2, "+++++|last node|+++++\n", 23);
        else if (tree1->right == 0)
            write(2, "(((((((null node)))))))\n", 25);
        parsing_tester(tree1->right);
    }
    else if (result_tree->type == REDIR)
    {
        write (2, "<><><>|redir|<><><> :", 22);
        tree2 = (t_redir *)result_tree;
        write(2, tree2->file, ft_strlen(tree2->file) +1);
        write(2, "\n", 1);
        parsing_tester(tree2->cmd);
    }
    else
    {
        write (2, "|||-----exec-----|||\n", 22);
        tree3 = (t_exec *)result_tree;
    }
}