/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_mapfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:56:57 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/02 11:10:38 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "parsing.h"

char	*ft_read_mapfile(int fd)
{
	char	*map;
	char	*get;
	char	*tmp;
	int		n;

	map = NULL;
	get = (char *)malloc(2);
	n = read(fd, get, 1);
	while (n > 0)
	{
		get[n] = '\0';
		if (!map && get)
			map = ft_dup(get);
		else
		{
			tmp = ft_join(map, get);
			free(map);
			map = tmp;
		}
		n = read(fd, get, 1);
	}
	free(get);
	return (map);
}
