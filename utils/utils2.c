/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 09:21:13 by hkhalil           #+#    #+#             */
/*   Updated: 2022/10/17 09:21:57 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

int valid_name(char *s)
{
    int i = 0;

    if (!ft_isalpha(s[i]) && s[i] != '_')
    {
        g_var = -2;
        return(0);
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