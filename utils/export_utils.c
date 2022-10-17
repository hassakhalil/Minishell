/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:52:42 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 09:56:35 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	greater_than_min(t_envvar **env, char **min, char *c)
{
	t_envvar	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, c) > 0)
		{
			free(min[0]);
			free(min[1]);
			min[0] = ft_strdup(tmp->name);
			min[1] = ft_strdup(tmp->value);
			break ;
		}
		tmp = tmp->next;
	}
}

void	new_min(t_envvar **env, char **min, char *c)
{
	t_envvar	*tmp;

	tmp = *env;
	while (tmp)
	{
		if ((ft_strcmp(min[0], tmp->name) > 0) && (ft_strcmp(tmp->name, c) > 0))
		{
			free(min[0]);
			free(min[1]);
			min[0] = ft_strdup(tmp->name);
			min[1] = ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
}

void	ft_print(char **min, char **c)
{
	if (min[1])
		printf("declare -x %s=\"%s\"\n", min[0], min[1]);
	else
		printf("declare -x %s\n", min[0]);
	free(*c);
	*c = ft_strdup(min[0]);
}

void	export_noargs(t_envvar **env)
{
	t_envvar	*tmp;
	char		**min;
	char		*c;
	int			n;

	if (!env && !(*env))
		return ;
	c = ft_strdup("");
	tmp = *env;
	min = malloc(sizeof(char *) * 2);
	min[0] = ft_strdup(tmp->name);
	min[1] = ft_strdup(tmp->value);
	n = ft_lstsize(tmp);
	while (n)
	{
		greater_than_min(env, min, c);
		new_min(env, min, c);
		ft_print(min, &c);
		n--;
	}
	free(c);
	free(min[0]);
	free(min[1]);
	free(min);
}
