/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:19:32 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 09:22:11 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char    **list_to_table(t_envvar *env)
{
    int n = ft_lstsize(env);
    int i = 0;
    char    **tab=malloc(sizeof(char *) * (n +1));

    while (env)
    {
        if (env->value)
        {
            tab[i] = ft_strjoin3(ft_strjoin(env->name, "="), env->value);
            i++;
        }
        env = env->next;
    }
    tab[i] = 0;
    return(tab);
}

char    *my_getenv(char *s, t_envvar *env)
{
    while (env)
    {
        if (!ft_strcmp(env->name, s))
            return(env->value);
        env = env->next;
    }
    return (0);
}

char	*ft_env_name(char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] != '$' && !is_white_space(s[i])
			&& s[i] != '\'' && s[i] != '\"')
		&& (ft_isalpha(s[i]) || ft_isdigit(s[i]) || s[i] == '_'))
		i++;
	return (ft_substr(s, 0, i));
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	is_white_space(int c)
{
	if (c == ' ' || c == '\n' || c == '\v'
		|| c == '\t' || c == '\f' || c == '\r')
		return (1);
	return (0);
}
