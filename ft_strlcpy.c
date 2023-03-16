/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 22:10:16 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/06 21:29:08 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	unsigned int	j;

	j = 0;
	while (src[j] != '\0')
		j++ ;
	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++ ;
		}
		dst[i] = '\0';
	}
	return (j);
}
