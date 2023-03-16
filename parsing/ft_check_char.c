/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:28:07 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/02 10:28:10 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_check_char(char *str, char c)
{
	int	i;

	i = -1;
	if (str && c)
	{
		while (str[++i])
			if (str[i] == c)
				return (true);
	}
	return (false);
}
