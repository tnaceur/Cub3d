/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 20:35:12 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/02 10:33:32 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_join(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	ret = (char *)malloc(sizeof(char) * (ft_len(s1) + ft_len(s2) + 1));
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

char	*ft_nchar(char c, int len)
{
	char	*tmp;
	int		i;

	if (len <= 0)
		ft_put_error("len or c ft_nchar");
	tmp = (char *)malloc(sizeof(char) * len + 1);
	if (!tmp)
		ft_put_error("tmp malloc error");
	i = 0;
	while (i < len)
	{
		tmp[i] = c;
		i++;
	}
	tmp[len] = 0;
	return (tmp);
}

void	ft_mjoin(char ***str, char c, int maxlen)
{
	int		i;
	int		len;
	char	*tmp;
	char	*to_free;

	if (!str || !*str || maxlen <= 0)
		ft_put_error("str or maxlen ft_mjoin");
	i = 0;
	to_free = NULL;
	while ((*str)[i])
	{
		len = ft_len((*str)[i]);
		if (len != maxlen)
		{
			to_free = (*str)[i];
			tmp = ft_nchar(c, maxlen - len);
			(*str)[i] = ft_join(to_free, tmp);
			free(tmp);
			free(to_free);
		}
		i++;
	}
}
