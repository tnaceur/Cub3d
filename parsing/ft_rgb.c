/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:09:53 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/07 20:46:06 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

long	ft_char_2_int(char *str)
{
	int		i;
	long	nb;

	i = 0;
	nb = 0;
	if (!str || !str[0])
		ft_put_error("str ft_char_2_int ");
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i] - 48);
		if (nb < 0 || nb > 255)
			return (-1);
		i++;
	}
	return (nb);
}

bool	ft_check_rgb(char *str, char *sch)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_check_char(sch, str[i]))
			return (false);
		i++;
	}
	return (true);
}

int	ft_get_rgb_help_1(char *str)
{
	int		start;
	int		end;
	int		v;
	char	*tmp;

	start = 0;
	end = 0;
	if (!str)
		ft_put_error("str ft_get_rgb_help_1");
	while (str[start] && str[start] == ' ')
		start++;
	end = start;
	while (str[end] && str[end] >= '0' && str[end] <= '9')
		end++;
	v = end;
	while (str[v] && str[v] == ' ')
		v++;
	if (str[v])
		return (-1);
	tmp = ft_sub(str, start, end - start);
	if (!tmp || !tmp[0])
		return (-1);
	end = ft_char_2_int(tmp);
	free(tmp);
	return (end);
}

void	ft_get_rgb_help(char *str, int **rgb)
{
	char	**tmp;
	int		i;
	int		v;

	if (!str)
		ft_put_error(" str ft_get_rgb_help");
	i = -1;
	v = 0;
	while (str[++i])
		if (str[i] == ',')
			v++;
	if (v != 2)
		return ;
	tmp = ft_strsplit(str, ',');
	if (!tmp)
		ft_put_error("ft_dup [ft_get_rgb_help]");
	if (ft_mlen(tmp) == 3)
	{
		i = -1;
		while (tmp[++i])
			(*rgb)[i] = ft_get_rgb_help_1(tmp[i]);
	}
	ft_free(tmp);
	return ;
}

void	ft_get_rgb(char *str, t_pdata *data, char c)
{
	int	i;

	i = 0;
	if (!data)
		ft_put_error("ft_get_rgb()");
	if (!str)
		return ;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == c)
	{
		i++;
		if (str[i] != ' ')
			return ;
		if (!ft_check_rgb(&str[i], "0123456789 ,"))
			return ;
		if (c == 'F')
			ft_get_rgb_help(&str[i], &(data->rgb_f));
		else
			ft_get_rgb_help(&str[i], &(data->rgb_c));
	}
}
