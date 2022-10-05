/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:17:14 by iakry             #+#    #+#             */
/*   Updated: 2022/10/05 11:33:36 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_list_remove_if(t_envvar **begin_list, void *data_ref, int (*cmp)())
{
	t_envvar	*current;
	t_envvar	*last;
	t_envvar	*next;

	current = *begin_list;
	last = ((void *)0);
	while (current)
	{
		next = current->next;
		if (cmp(current->name, data_ref) == 0)
		{
			if (last)
				last->next = current->next;
			else
				*begin_list = current->next;
			free(current);
			current = ((void *)0);
		}
		last = current;
		current = next;
	}	
}

void	ft_lstadd_back(t_envvar **head, t_envvar *new)
{
	t_envvar	*temp;

	if (!(*head))
	{
		(*head) = new;
		return ;
	}
	temp = (*head);
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_envvar *ft_lstadd_new(void *n, void *v)
{
    t_envvar *env;
    
    env = malloc(sizeof(*env));
    if (!env)
        return NULL;
    env->name = n;
    env->value = v;
    env->next = NULL;
    return (env);
}

t_envvar *init_envvar(char **env)
{
    char **p;
    int i = 0;
    t_envvar *new;

    new = NULL;
    while (env[i])
    {
        p = ft_split(env[i++], '=');
        ft_lstadd_back(&new, ft_lstadd_new(p[0], p[1]));
    }
    return (new);
}