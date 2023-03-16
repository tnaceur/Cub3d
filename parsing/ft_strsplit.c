/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:12:06 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/06 14:54:49 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_nw(char *ss, char cc)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (ss[i])
	{
		if (ss[i] != cc && (ss[i + 1] == cc || ss[i + 1] == '\0'))
		{
			n++;
		}
		i++;
	}
	return (n);
}

int	ft_index(char *sr, char ch, int i)
{
	while (sr[i])
	{
		if (sr[i] != ch && (sr[i + 1] == ch || sr[i + 1] == '\0'))
			break ;
		i++;
	}
	return (i);
}

char	**ft_strsplit(char *str, char c)
{
	int		i;
	int		j;
	int		index;
	char	**ret;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	index = ft_index(str, c, i);
	ret = (char **)malloc(sizeof(char *) * (ft_nw(str, c) + 1));
	if (!ret)
		return (NULL);
	while (j < ft_nw(str, c))
	{
		while (str[i] == c)
			i++;
		ret[j] = ft_sub(str, i, index - i + 1);
		i = ++index;
		index = ft_index(str, c, i);
		j++;
	}
	ret[j] = NULL;
	return (ret);
}
