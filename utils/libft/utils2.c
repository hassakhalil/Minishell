/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:51:44 by iakry             #+#    #+#             */
/*   Updated: 2022/09/17 18:38:06 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*s;

	if (!s1 || !s2)
		return (0);
	s = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s)
		return (0);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = 0;
	return (s);
}

char	*ft_strjoin2(char const *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc (sizeof(char) * (ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '/';
	j = 0;
	while (s2[j] != '\0')
	{
		str[++i] = s2[j++];
	}
	str[++i] = '\0';
	return (str);
}