/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:29:50 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/02 10:29:51 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "parsing.h"

char	*ft_dup(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_len(str) + 1));
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
