/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 10:54:51 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/06 21:25:44 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"cub.h"

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	ptr = malloc(i + j + 1);
	i = -1;
	while (s1[++i])
		ptr[i] = s1[i];
	j = 0;
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = '\0';
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return (ptr);
}
