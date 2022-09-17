/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 10:07:43 by iakry             #+#    #+#             */
/*   Updated: 2022/09/17 18:38:18 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	if (src < dest)
	{
		i = n - 1;
		while (0 <= i)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return ((void *)dest);
}

int	number_of_strings(char const *s, char c)
{
	int	i;
	int	j;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		j = 0;
		while (s[i] != c && s[i])
		{
			j = 1;
			i++;
		}
		if (j == 1)
			n++;
		if (s[i])
			i++;
	}
	return (n);
}

char	*malloc_free(char **x, int k, int j)
{
	x[k] = malloc(j + 1);
	if (!x[k])
	{
		while (k > 0)
		{
			free(x[k - 1]);
			k--;
		}
		free(x);
		x = NULL;
		return (0);
	}
	return (x[k]);
}

void	ft_split_1(char const *s, char c, char **x, int n)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (n > 0)
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i + j] != c && s[i + j])
			j++;
		if (!malloc_free(x, k, j))
			return ;
		if (ft_memmove(x[k], &s[i], j))
		{
			x[k][j] = 0;
			k++;
			n--;
			i = i + j;
		}
	}
	x[k] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**x;
	int		n;

	if (!s)
		return (0);
	n = number_of_strings(s, c);
	x = malloc((n + 1) * sizeof(char *));
	if (!x)
		return (0);
	ft_split_1(s, c, x, n);
	return (x);
}