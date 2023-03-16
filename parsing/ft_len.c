/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:28:15 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/03 16:48:27 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_len(char *str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

int	ft_mlen(char **str)
{
	int	i;

	i = 0;
	if (str)
		while (str[i])
			i++;
	return (i);
}

int	ft_maxlen(char **str)
{
	int	i;
	int	len;
	int	t_len;

	i = 0;
	len = -1;
	t_len = 0;
	if (str)
	{
		while (str[i])
		{
			t_len = ft_len(str[i]);
			if (len < t_len)
				len = t_len;
			i++;
		}
	}
	return (len);
}
