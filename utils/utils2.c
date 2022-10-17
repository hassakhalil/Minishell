/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:21:13 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 17:59:49 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int	valid_name(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
	{
		g_var = -2;
		return (0);
	}
	while (s[i])
	{
		if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]) && s[i] != '_')
		{
			g_var = -2;
			return (0);
		}
		i++;
	}
	return (1);
}

int	complete_pipe(char *buff)
{
	int	i;
	int	c;
	int	k;

	i = 0;
	c = 0;
	k = 0;
	while (buff[i])
	{
		if (!is_white_space(buff[i]))
		{
			c = buff[i];
			if (c == '|')
			{
				if (++k > 1)
					return (1);
			}
			else if (k)
				k--;
		}
		i++;
	}
	if (c == '|')
		return (1);
	return (0);
}

void	errors5(int flag)
{
	if (flag == 20)
	{
		perror("missing file for redirection");
		exit(EXIT_FAILURE);
	}
	if (flag == 21)
	{
		perror("syntax error");
		exit(EXIT_FAILURE);
	}
	if (flag == 22)
	{
		perror("Too many args");
		exit(EXIT_FAILURE);
	}
	if (flag == 23)
	{
		write(2, "syntax error near unexpected token `|'\n", 40);
		exit(58);
	}
}

char	*expand_file(char *arg)
{
	int		i;
	char	*new_arg;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1]
			&& (arg[i + 1] == '\'' || arg[i + 1] == '\"'))
		{
			new_arg = ft_strjoin3(ft_substr(arg, 0, i), &arg[i + 1]);
			free(arg);
			arg = ft_strdup(new_arg);
			free(new_arg);
		}
		i++;
	}
	return (arg);
}
