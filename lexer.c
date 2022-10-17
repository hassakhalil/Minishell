/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkhalil <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 15:26:29 by iakry             #+#    #+#             */
/*   Updated: 2022/10/17 11:24:59 by hkhalil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote(int *ret, char **s, char **es)
{
	int	c;

	c = 0;
	*ret = 'a';
	while (*s < *es && !ft_strchr(" \t\r\n\v", **s) && !ft_strchr("<|>", **s))
	{
		if (**s == '\'' || **s == '\"')
		{
			c = **s;
			(*s)++;
			while (*s < *es && **s != c)
				(*s)++;
			if (*s == *es)
				errors(NULL, 21);
		}
		if (*s != *es)
			(*s)++;
	}
}

void	gettoken_h(int *ret, char **s, char **es)
{
	if (**s == '|')
		(*s)++;
	else if (**s == '>')
	{
		(*s)++;
		if (**s == '>')
		{
			(*s)++;
			*ret = '+';
		}
	}
	else if (**s == '<')
	{
		(*s)++;
		if (**s == '<')
		{
			(*s)++;
			*ret = '*';
		}
	}
	else
		quote(ret, s, es);
}

int	gettoken(char **ss, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ss;
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (*s == 0)
		return (ret);
	gettoken_h(&ret, &s, &es);
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	*ss = s;
	return (ret);
}

int	peek(char **ss, char *es, char *toks)
{
	char	*s;

	s = *ss;
	while (s < es && ft_strchr(" \t\r\n\v", *s))
		s++;
	*ss = s;
	return (*s && ft_strchr(toks, *s));
}
