/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 07:14:38 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/15 09:06:22 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	if_exist_add(t_envvar **env, char **s, int flag)
{
	while (env && *env)
	{
		if (!ft_strcmp((*env)->name, s[0]))
		{
			if (flag && s[1])
				(*env)->value = ft_strdup(s[1]);
			return (1);
		}
		(*env) = (*env)->next;
	}
	return (0);
}

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

void	global_env(t_envvar **env, char *s, t_envvar *addr)
{
	char	**v;

	v = ft_split(s, '=');
	if (!v[1])
	{
		free(v[1]);
		v[1] = ft_strdup("");
	}
	if (if_exist_add(&addr, v, 1))
		;
	else
	{
		if (valid_name(v[0]))
			ft_lstadd_back(env,
				ft_lstadd_new(ft_strdup(v[0]), ft_strdup(v[1])));
		else
		{
			GLOBAL = -2;
			printf("export: `%s': not a valid identifier\n", s);
		}
	}
	free(v[0]);
	free(v[1]);
	free(v);
}

void	local_env(t_envvar **env, char *s, t_envvar	*addr)
{
	if (if_exist_add(&addr, &s, 0))
		;
	else if (valid_name(s))
		ft_lstadd_back(env,
			ft_lstadd_new(ft_strdup(s), NULL));
	else
	{
		GLOBAL = -2;
		printf("export: `%s': not a valid identifier\n", s);
	}
}

void	ft_export(t_exec *cmd, t_envvar **env)
{
	int			i;
	t_envvar	*addr;

	i = 1;
	if (!cmd->argv[i])
		export_noargs(env);
	while (cmd->argv[i])
	{
		addr = *env;
		if (ft_strchr(cmd->argv[i], '='))
			global_env(env, cmd->argv[i], addr);
		else
			local_env(env, cmd->argv[i], addr);
		i++;
	}
}
