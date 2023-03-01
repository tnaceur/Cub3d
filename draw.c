/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:13:46 by tnaceur           #+#    #+#             */
/*   Updated: 2023/02/27 23:57:41 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	d_wall_2d(t_game *game, int x, int y, int color)
{
	int	a;
	int	b;

	a = x;
	while (a < x + 40)
	{
		b = y;
		while (b < y + 40)
		{
			my_mlx_pixel_put(game, b * 0.1, a * 0.1, color);
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
				d_wall_2d(game, i * 40, j * 40, game->bl);
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

void	draw_line(t_game *game, double angle, int color, int tall)
{
	t_line	line;

	line.x2 = game->p_x + cos(angle) * tall;
	line.y2 = game->p_y + sin(angle) * tall;
	line.dx = line.x2 - game->p_x;
	line.dy = line.y2 - game->p_y;
	if (fabs(line.dx) > fabs(line.dy))
		line.steps = fabs(line.dx);
	else
		line.steps = fabs(line.dy);
	line.xinc = line.dx / line.steps;
	line.yinc = line.dy / line.steps;
	line.x2 = game->p_x;
	line.y2 = game->p_y;
	line.i = 0;
	while (++line.i <= line.steps && game->map[(int)floor(line.x2 / 40)]
		&& game->map[(int)floor(line.x2 / 40)][(int)floor(line.y2 / 40)] != '1')
	{
		my_mlx_pixel_put(game, line.y2 * 0.1,
			line.x2 * 0.1, color);
		line.x2 += line.xinc;
		line.y2 += line.yinc;
	}
	game->dst = distance(game, line.x2, line.y2);
}

void	d_wall_3d(t_game *game, double x, double y, double w_height)
{
	double	i;
	double	j;
	double	w_width;
	int		color;

	color = mlx_get_color_value(game->mlx, 13159935);
	w_width = 1;
	i = x;
	while (i < x + w_height)
	{
		j = y;
		while (j < y + w_width)
		{
			if (j > WIDTH || i > HEIGHT
				|| j < 0 || i < 0)
				break ;
			my_mlx_pixel_put(game, j, i, color);
			j++;
		}
		i++;
	}
}
