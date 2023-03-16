/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extension.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:30:05 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/02 10:30:52 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_check_ext(char *str, char *ext)
{
	int	i;
	int	len;
	int	ext_len;

	i = 1;
	len = ft_len(str);
	ext_len = ft_len(ext);
	if (ext && str && len >= 5)
	{
		while (i <= 4)
		{
			if (str[len - i] != ext[ext_len - i])
				break ;
			i++;
		}
		if (i == 5)
			if (str[len - i] != '/')
				return (true);
	}
	return (false);
}
