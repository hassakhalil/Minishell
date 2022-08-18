#include "minishell.h"

void errors(char *msg)
{
    printf("%s\n", msg);
    //clean everything
    exit(1);
}

void    parsing_tester(cmd *result_tree, env *env, int flag)
{
    int id;
    pip *tree1;
    redir *tree2;
    exec *tree3;

    if (result_tree->type == '|')
    {
        write (2, "-----pipe-----\n", 16);
        tree1 = (pip *)result_tree;
        id = fork();
        if (id < 0)
            errors("fork error");
        if (id == 0)
        {
            write (2, "-----pipe->left-----\n", 22);
            parsing_tester(tree1->left,env, flag);
            return ;
        }
        write (2, "-----pipe->right-----\n", 22);
        parsing_tester(tree1->right,env, flag);
        wait(0);
        return ;
     }
    else if (result_tree->type == '>')
    {
        write (2, "-----redir-----\n", 17);
        tree2 = (redir *)result_tree;
        parsing_tester(tree2->cmd, env, flag);
        return ;
    }
    else
    {
        write (2, "-----exec-----\n", 16);
        //printf("%s\n", env->path[6]);
        //execve("/usr/local/bin/grep", tree3->argv, env->path);
        //errors("execve error");
        //
        return ;
    } 
}