/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 11:31:53 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/07 20:46:52 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_cmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		ft_put_error("ft_cmp");
	if (ft_len(s1) != ft_len(s2))
		return (false);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}

bool	ft_strstr(char *str, char *sch)
{
	int	i;
	int	j;

	if (!str || !sch)
		ft_put_error("ft_strstr");
	i = 0;
	while (str[i])
	{
		j = 0;
		if (str[i] == sch[j])
		{
			while (str[i + j] && sch[j] && str[i + j] == sch[j])
				j++;
			if (ft_len(sch) == j)
				return (true);
		}
		i++;
	}
	return (false);
}

bool	ft_strstr_1(char *str, char *sch)
{
	int	i;
	int	v;

	i = 0;
	if (!sch)
		ft_put_error("sch ft_strstr_1");
	v = 0;
	while (sch[i])
	{
		if (ft_check_char(str, sch[i]))
			v++;
		i++;
	}
	if (v == ft_len(sch))
		return (true);
	return (false);
}

bool	ft_sch(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		ft_put_error("str ft_sch");
	while (str[i])
	{
		if (str[i] != c)
			return (false);
		i++;
	}
	return (true);
}
