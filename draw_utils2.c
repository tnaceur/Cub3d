/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:43:56 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/06 09:46:36 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	wall_att(t_game *game, double x2, double y2)
{
	int	x;
	int	y;

	x = floor(x2 / 40);
	y = floor(y2 / 40);
	if (x > 0 && y > 0 && game->map[x] && game->map[x][y] != '1')
		return (1);
	return (0);
}

int	player_pos(t_game *game, double x2, double y2)
{
	int	x;
	int	y;

	x = floor(x2 / 40);
	y = floor(y2 / 40);
	if ((x >= 0 && y >= 0 && game->map[x] && game->map[x][y] == '1')
		|| x >= game->hieght || y >= (int)ft_strlen(game->map[x]))
		return (0);
	x = floor((x2 + 1) / 40);
	y = floor(y2 / 40);
	if (x >= 0 && y >= 0 && game->map[x] && game->map[x][y] == '1')
		return (0);
	x = floor(x2 / 40);
	y = floor((y2 + 1) / 40);
	if (x >= 0 && y >= 0 && game->map[x] && game->map[x][y] == '1')
		return (0);
	x = floor((x2 - 1) / 40);
	y = floor(y2 / 40);
	if (x >= 0 && y >= 0 && game->map[x] && game->map[x][y] == '1')
		return (0);
	x = floor(x2 / 40);
	y = floor((y2 - 1) / 40);
	if (x >= 0 && y >= 0 && game->map[x] && game->map[x][y] == '1')
		return (0);
	return (1);
}
