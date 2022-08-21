/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iakry <iakry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:15:07 by iakry             #+#    #+#             */
/*   Updated: 2022/08/04 11:15:24 by iakry            ###   ########.fr       */
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
	if (p == 0)
		return (0);
	while (str[j])
	{
		p[j] = str[j];
		j++;
	}
	p[j] = '\0';
	return (p);
}