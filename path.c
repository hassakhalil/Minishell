/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:07:20 by iakry             #+#    #+#             */
/*   Updated: 2022/09/22 01:26:38 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *envpath(void)
{
    t_env *envp;
    char  *p;

    envp = malloc(sizeof(*envp));
    p = getenv("PATH");
    if (!p)
        return (NULL);
    envp->path = ft_split(p, ':');
    return envp;
}

char *getpath(char *buff)
{
    char *s = buff;
    char path[100];
    int i = 0;
    
    if (!ft_strncmp(s, "cd ", 3))
    {
        s = s+3;
        while (*s == ' ')
            s++;
        while (*s != ' ' && *s)
            path[i++] = *s++;
        path[i] = 0;
        s = path;
        return (s);
    }
    return NULL;
}



//TMPDIR SHELL HOME SSH_AUTH_SOCK Apple_PubSub_Socket_Render LOGNAME XPC_SERVICE_NAME COMMAND_MODE MallocNanoZone USER SECURITYSESSIONID XPC_FLAGS __CF_USER_TEXT_ENCODING ORIGINAL_XDG_CURRENT_DESKTOP SHLVL PWD OLDPWD HOMEBREW_CACHE HOMEBREW_TEMP TERM_PROGRAM TERM_PROGRAM_VERSION LANG COLORTERM GIT_ASKPASS VSCODE_GIT_ASKPASS_NODE VSCODE_GIT_ASKPASS_EXTRA_ARGS VSCODE_GIT_ASKPASS_MAIN VSCODE_GIT_IPC_HANDLE VSCODE_INJECTION ZDOTDIR TERM
//_