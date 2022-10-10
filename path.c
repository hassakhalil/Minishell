/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:07:20 by iakry             #+#    #+#             */
/*   Updated: 2022/10/10 17:33:02 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **envpath(t_envvar *env)
{
    char **path = NULL;

    while (env)
    {
        if (!ft_strcmp(env->name, "PATH"))
            path = ft_split(env->value, ':');
        env = env->next;
    }    
    return (path);
}




//TMPDIR SHELL HOME SSH_AUTH_SOCK Apple_PubSub_Socket_Render LOGNAME XPC_SERVICE_NAME COMMAND_MODE MallocNanoZone USER SECURITYSESSIONID XPC_FLAGS __CF_USER_TEXT_ENCODING ORIGINAL_XDG_CURRENT_DESKTOP SHLVL PWD OLDPWD HOMEBREW_CACHE HOMEBREW_TEMP TERM_PROGRAM TERM_PROGRAM_VERSION LANG COLORTERM GIT_ASKPASS VSCODE_GIT_ASKPASS_NODE VSCODE_GIT_ASKPASS_EXTRA_ARGS VSCODE_GIT_ASKPASS_MAIN VSCODE_GIT_IPC_HANDLE VSCODE_INJECTION ZDOTDIR TERM
//_