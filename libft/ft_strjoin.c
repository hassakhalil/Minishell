/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iakry <iakry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:51:44 by iakry             #+#    #+#             */
/*   Updated: 2022/08/05 11:11:22 by iakry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	join(char	*dest, const char	*src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = ft_strlen((char *)dest);
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen((char *)s1) == 0 && ft_strlen((char *)s2) == 0)
		return (ft_strdup(""));
	else if (ft_strlen((char *)s1) == 0 && s2 != NULL)
		return ((char *)ft_strdup(s2));
	else if (ft_strlen((char *)s2) == 0 && s1 != NULL)
		return ((char *)ft_strdup(s1));
	p = malloc(sizeof(char) * (ft_strlen((char *)s1) + ft_strlen((char *)s2)) + 1);
	if (!p)
		return (0);
	p[0] = '\0';
	join(p, s1);
	join(p, s2);
	return (p);
}