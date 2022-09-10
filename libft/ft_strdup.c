/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:15:07 by iakry             #+#    #+#             */
/*   Updated: 2022/09/10 15:57:03 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		j;
	char	*p;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	p = (char *)malloc((i + 1) * sizeof(char));
	while (str[j])
	{
		p[j] = str[j];
		j++;
	}
	p[j] = '\0';
	return (p);
}