/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iakry <iakry@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:02:52 by iakry             #+#    #+#             */
/*   Updated: 2022/08/04 09:43:54 by iakry            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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