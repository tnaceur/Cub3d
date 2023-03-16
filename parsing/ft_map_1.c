/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:34:27 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/07 20:21:58 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_bypass_char(char *str, int *i, char c, int revrse)
{
	if (!str || *i < 0 || *i >= ft_len(str))
		ft_put_error("str  or  i ft_bypass_char");
	if (revrse == 0)
	{
		while (str[*i] && str[*i] == c)
			(*i)++;
	}
	else if (revrse == -1)
	{
		while (str[*i] && str[*i] != c)
			(*i)++;
	}
	else
	{
		while ((*i) > 0 && str[*i] == c)
			(*i)--;
	}
}

int	ft_line_cmp(char *str, char *sch)
{
	char	*line;
	int		start;
	int		end;

	if (!str || !sch)
		ft_put_error("ft_get_line_cmp");
	end = 0;
	line = NULL;
	while (str[end])
	{
		start = end;
		ft_bypass_char(str, &start, '\n', 0);
		end = start;
		ft_bypass_char(str, &end, '\n', -1);
		line = ft_sub(str, start, end - start);
		if (!line)
			ft_put_error("line ft_get_line_cmp");
		if (ft_cmp(line, sch))
		{
			free(line);
			return (start);
		}
		free(line);
	}
	return (-1);
}

void	ft_delete_line(char **str, int start)
{
	if (!str || start == -1)
		ft_put_error("star == -1 ft_delete_line");
	while ((*str)[start] && (*str)[start] != '\n')
	{
		(*str)[start] = ' ';
		start++;
	}
}

bool	ft_valid_char_help(t_pmap *dmap, int y, int x, char *sch)
{
	char	**tmp;

	if (!dmap || !dmap->map)
		ft_put_error("dmap ft_valid_char_help");
	if (x < 1 || x > dmap->len - 1 || y < 1 || y >= dmap->mlen - 1)
		return (false);
	tmp = dmap->map;
	if (tmp[y][x + 1] && tmp[y][x - 1] && (!ft_check_char(sch, tmp[y][x + 1]) \
	|| !ft_check_char(sch, tmp[y][x - 1])))
		return (false);
	if (tmp[y + 1][x] && tmp[y - 1][x] && (!ft_check_char(sch, tmp[y + 1][x]) \
	|| !ft_check_char(sch, tmp[y - 1][x])))
		return (false);
	return (true);
}

bool	ft_valid_char(t_pmap *dmap, char to_check, char *sch)
{
	int		x;
	int		y;
	char	**tmp;

	tmp = dmap->map;
	if (!tmp)
		ft_put_error("tmp ft_valid_char");
	y = 0;
	while (tmp[y])
	{
		x = 0;
		while (tmp[y][x])
		{
			if (tmp[y][x] == to_check)
				if (!ft_valid_char_help(dmap, y, x, sch))
					return (false);
			x++;
		}
		y++;
	}
	return (true);
}
