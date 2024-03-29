/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:13:18 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/02 11:13:32 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	start_2_len(char *str, int st, int len)
{
	int	i;
	int	tot;

	i = 0;
	if (!str || st >= ft_len(str))
		return (-1);
	if (ft_len(str) <= len)
		len = ft_len(str) - st;
	tot = st + len;
	while (st < tot)
	{
		st++;
		i++;
	}
	return (i);
}

char	*ft_sub(char *str, int start, int len)
{
	int		i;
	int		s2l;
	char	*ret;

	s2l = start_2_len(str, start, len);
	ret = (char *)malloc((s2l + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < s2l)
	{
		ret[i] = str[start];
		start++;
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
