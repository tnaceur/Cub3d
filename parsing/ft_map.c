/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 10:05:43 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/08 10:29:21 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_check_new_line(t_pdata *data)
{
	int	start;

	if (!data || !data->map->mapline)
		ft_put_error("data ft_check_new_line");
	start = 0;
	ft_bypass_char(data->map->mapline, &start, '\n', 0);
	while (data->map->mapline[start])
	{
		if (data->map->mapline[start] == '\n' \
		&& data->map->mapline[start + 1] == '\n')
			return (false);
		start++;
	}
	return (true);
}

int	ft_check_element(char *str, char *sch, char *to_count)
{
	int	i;
	int	v;

	i = -1;
	v = 0;
	if (!str || !str[0])
		ft_put_error("str ft_check_element");
	while (str[++i])
	{
		if (!ft_check_char(sch, str[i]))
		{
			if (ft_check_char(to_count, str[i]))
				v += (int)str[i];
			else
				return (-1);
		}
	}
	if (v == 0)
		return (-2);
	if (v > 130)
		return (-3);
	if (v < 130)
		return (v);
	return (1);
}

void	ft_check_map_helper(char *str, char **mstr, char **mmap)
{
	int	i;
	int	lo;

	if (!str || !mstr || !*mstr)
		ft_put_error("str or mstr ft_check_map_helper");
	i = 0;
	lo = 0;
	while (mstr[i] && lo < 6)
	{
		if (!ft_sch(mstr[i], ' '))
		{
			lo++;
			ft_delete_line(&str, ft_line_cmp(str, mstr[i]));
		}
		i++;
	}
	while (str[i] && (str[i] == ' ' || str[i] == '\n'))
		i++;
	while (i > 0 && str[i] != '\n')
		i--;
	*mmap = ft_dup(&str[i + 1]);
}

void	ft_check_map(t_pdata *data)
{
	int	i;

	i = 0;
	ft_check_map_helper(data->full_map, data->map_file, &(data->map->mapline));
	if (!ft_strstr_1(data->map->mapline, "1\n"))
		ft_put_error("charater not found");
	if (!ft_check_new_line(data))
		ft_put_error("Invalide line (new line)");
	i = ft_check_element(data->map->mapline, "\n 01", "NSWE");
	if (i == -1)
		ft_put_error("Invalide charater");
	if (i == -2)
		ft_put_error("You need one player's starting position");
	if (i == -3)
		ft_put_error("More than one player's starting position");
	data->map->o = (char)i;
	data->map->map = ft_strsplit(data->map->mapline, '\n');
	data->map->basic_map = ft_strsplit(data->map->mapline, '\n');
	data->map->len = ft_maxlen(data->map->map);
	data->map->mlen = ft_mlen(data->map->map);
	ft_mjoin(&(data->map->map), '#', data->map->len);
	if (!ft_valid_char(data->map, '0', "10NSWE"))
		ft_put_error("Invalid map (empty space)");
	if (!ft_valid_char(data->map, data->map->o, "10"))
		ft_put_error("Invalid map (player)");
}
