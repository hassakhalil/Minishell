#include <unistd.h>
#include <stdio.h>

#define name = "hello";

/*void print2DUtil(struct cmd *cmd, int space)
{
    // Base case
    if (cmd == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(cmd->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", cmd->type);
 
    // Process left child
    print2DUtil(cmd->type, space);
}*/

/*
 __    __     __     __   __     __     ______     __  __     ______     __         __        
/\ "-./  \   /\ \   /\ "-.\ \   /\ \   /\  ___\   /\ \_\ \   /\  ___\   /\ \       /\ \       
\ \ \-./\ \  \ \ \  \ \ \-.  \  \ \ \  \ \___  \  \ \  __ \  \ \  __\   \ \ \____  \ \ \____  
 \ \_\ \ \_\  \ \_\  \ \_\\"\_\  \ \_\  \/\_____\  \ \_\ \_\  \ \_____\  \ \_____\  \ \_____\ 
  \/_/  \/_/   \/_/   \/_/ \/_/   \/_/   \/_____/   \/_/\/_/   \/_____/   \/_____/   \/_____/ 
                                                                                              
*/

int main()
{
    printf("\033[1;33m");
    printf("\n __    __     __     __   __     __     ______     __  __     ______     __         __        \n");
    printf("/\\  -./  \\   /\\ \\   /\\  -.\\ \\   /\\ \\   /\\  ___\\   /\\ \\_\\ \\   /\\  ___\\   /\\ \\       /\\ \\       \n");
    printf("\\ \\ \\-./\\ \\  \\ \\ \\  \\ \\ \\-.  \\  \\ \\ \\  \\ \\___  \\  \\ \\  __ \\  \\ \\  __\\   \\ \\ \\____  \\ \\ \\____  \n");
    printf(" \\ \\_\\ \\ \\_\\  \\ \\_\\  \\  \\_\\ \\_\\  \\ \\_\\  \\/\\_____\\  \\ \\_\\ \\_\\  \\ \\_____\\  \\ \\_____\\  \\ \\_____\\ \n");
    printf("  \\/_/  \\/_/   \\/_/   \\/_/ \\/_/   \\/_/   \\/_____/   \\/_/\\/_/   \\/_____/   \\/_____/   \\/_____/ \n\n\n");
    printf("\033[0m");
    return 0;
}