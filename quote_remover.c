/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_remover.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 05:09:26 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/14 05:43:35 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quote_remover(char *s)
{
	int		i;
	int		j;
	int		c;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * ft_strlen(s) + 1);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			c = s[i++];
			while (s[i] && s[i] != c)
				new[j++] = s[i++];
			if (s[i])
				i++;
		}
		else
			new[++j] = s[++i];
	}
	new[j] = 0;
	free(s);
	return (new);
}
