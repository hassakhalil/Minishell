/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 22:14:53 by hkhalil           #+#    #+#             */
/*   Updated: 2022/09/19 22:15:30 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] > s2[i])
			return ((unsigned char)(s1[i] - s2[i]));
		else if (s1[i] < s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	return (0);
}