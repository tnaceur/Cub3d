/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:13:46 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/08 12:20:24 by tnaceur          ###   ########.fr       */
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
			if (!my_mlx_pixel_put(game, b * 0.1, a * 0.1, color))
				break ;
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

void	put_player(t_game *game, int color)
{
	double	i;
	double	j;

	i = game->p_x;
	while (i < game->p_x + 10)
	{
		j = game->p_y;
		while (j < game->p_y + 10)
			my_mlx_pixel_put(game, (j++) * 0.1, i * 0.1, color);
		i++;
	}
}

int	line_loop(t_game *game, t_line *line, double *x_step, double *y_step)
{
	if (!wall_att(game, line->x2 + *x_step, line->y2))
	{
		line->x2 += *x_step;
		if (*x_step > 0)
			game->face = 1;
		else
			game->face = 2;
		return (1);
	}
	if (!wall_att(game, line->x2, line->y2 + *y_step))
	{
		line->y2 += *y_step;
		if (*y_step > 0)
			game->face = 3;
		else
			game->face = 4;
		return (1);
	}
	return (0);
}

void	draw_line(t_game *game, double angle, int color, int tall)
{
	t_line	line;
	double	x_step;
	double	y_step;
	int		i;

	line.x2 = game->p_x;
	line.y2 = game->p_y;
	x_step = cos(angle);
	y_step = sin(angle);
	i = 0;
	while (wall_att(game, line.x2, line.y2))
	{
		if (i < tall)
			my_mlx_pixel_put(game, line.y2 * 0.1, line.x2 * 0.1, color);
		if (line_loop(game, &line, &x_step, &y_step))
			break ;
		line.x2 += x_step;
		line.y2 += y_step;
		i++;
	}
	game->wall_hitx = line.x2;
	game->wall_hity = line.y2;
	game->dst = distance(game, line.x2, line.y2);
}
