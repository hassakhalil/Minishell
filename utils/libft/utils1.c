/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 11:15:07 by iakry             #+#    #+#             */
/*   Updated: 2022/09/17 18:41:23 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest == src)
		return (dest);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*copy;

	copy = malloc(ft_strlen(s) + 1);
	if (!copy)
		return (0);
	return (ft_memcpy(copy, s, ft_strlen(s) + 1));
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return ((char *)&s[i]);
	if (s[i] == c)
		return ((char *)&s[i]);
	return (0);
}

char	*ft_strnstr(char	**big, char *little, size_t l)
{
	size_t	i;
	size_t	j;
    size_t  n;
	char	**big1;

	i = 0;
    n = 0;
	if (big[n][0] == '\0' || little[0] == '\0')
		if (big[n][0] == '\0')
			return (NULL);
	big1 = big;
	if (little == NULL)
		return (big1[n]);
    while (big1[n][i] != 0)
    {
	    while (i < l && big1[n][i] != 0)
	    {
		    j = 0;
		    while (big1[n][i + j] == little[j])
		    {
			    if (j == (ft_strlen(little)) - 1 && i + j < l)
				    return (&*big1[n]);
			    j++;
		    }
		    i++;
        }
        n++;
	}
	return (NULL);
}