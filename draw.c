/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:13:46 by tnaceur           #+#    #+#             */
/*   Updated: 2023/02/17 09:14:12 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	d_wall(t_game *game, int x, int y, int color)
{
	int	a;
	int	b;

	a = x;
	while (a <= x + 40)
	{
		b = y;
		while (b < y + 40)
		{
			my_mlx_pixel_put(game, b, a, color);
			b++;
		}
		a++;
	}
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
				d_wall(game, i * 40, j * 40, game->bl);
			else if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				if (!game->p_x && !game->p_y)
				{
					game->p_x = i * 40;
					game->p_y = j * 40;
				}
			}
			j++;
		}
		i++;
	}
}
