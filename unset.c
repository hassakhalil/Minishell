/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 05:24:09 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 07:11:50 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_first(t_envvar **env, t_envvar *list)
{
	t_envvar	*tmp;
	int			n;

	n = ft_lstsize(*env);
	tmp = list;
	if ((*env)->next)
		*env = (*env)->next;
	free(tmp->name);
	free(tmp->value);
	if (n > 1)
		free(tmp);
	if (n == 1)
	{
		*env = NULL;
		list = NULL;
	}
}

void	remove_last(t_envvar *list, t_envvar *prev)
{
	t_envvar	*tmp;

	tmp = list;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	prev->next = NULL;
}

void	remove_mid(t_envvar *list, t_envvar *prev)
{
	t_envvar	*tmp;
	t_envvar	*next;

	tmp = list;
	next = list->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	prev->next = next;
}

void	if_exist_delete(t_envvar **env, char *s)
{
	t_envvar	*prev;
	t_envvar	*list;
	int			i;

	prev = *env;
	list = *env;
	i = 0;
	while (list)
	{
		if (!ft_strcmp(list->name, s))
		{
			if (i == 0)
				remove_first(env, list);
			else if (i + 1 == ft_lstsize(*env))
				remove_last(list, prev);
			else
				remove_mid(list, prev);
			break ;
		}
		prev = list;
		if (list)
			list = list->next;
		i++;
	}
}

void	ft_unset(t_exec *cmd, t_envvar **env)
{
	int	i;

	i = 1;
	while (cmd->argv[i])
	{
		if (!valid_name(cmd->argv[i]))
		{
			GLOBAL = -2;
			printf("unset: `%s': not a valid identifier\n", cmd->argv[i]);
		}
		else
			if_exist_delete(env, cmd->argv[i]);
		i++;
	}
}
