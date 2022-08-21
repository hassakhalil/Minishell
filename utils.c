/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iakry <iakry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 11:34:14 by iakry             #+#    #+#             */
/*   Updated: 2022/08/01 13:05:05 by iakry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t  ft_strlen(char *s)
{
    size_t i;

    i = 0;
    while (s[i])
		i++;
    return (i);
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

int	forkk(void)
{
	int pid;
	
	pid = fork();
	if(pid == -1)
		perror("fork");
	return pid;
}

void	err_putchar(char *s)
{
	int i;

	i = -1;
	while(s[++i])
		write(2, &s[i], 1);
}

char	*mkcopy(char *s, char *es)
{
	int n;
	
	n = es - s;
	char *c = malloc(n+1);
	if (!c)
		perror("error");
	strncpy(c, s, n);
	c[n] = 0;
	return c;
}