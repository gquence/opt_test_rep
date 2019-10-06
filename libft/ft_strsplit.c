/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelessa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 04:19:30 by dmelessa          #+#    #+#             */
/*   Updated: 2019/02/14 18:42:23 by dmelessa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_wc(char const *s, char c)
{
	unsigned int wc;

	wc = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		while (*s && *s != c)
			s++;
		wc++;
		while (*s && *s == c)
			s++;
	}
	return (wc);
}

char				**ft_strsplit(char const *s, char c)
{
	char		**p;
	const char	*estr;
	size_t		i;

	if (!s || !(p = (char **)malloc((ft_wc(s, c) + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		estr = s;
		while (*estr && *estr != c)
			estr++;
		*(p + i++) = ft_strsub(s, 0, estr - s);
		s = estr;
		while (*s && *s == c)
			s++;
	}
	*(p + i) = NULL;
	return (p);
}
