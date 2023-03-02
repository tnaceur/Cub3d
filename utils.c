/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 18:22:26 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/02 10:04:14 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	distance(t_game *game, double x1, double y1)
{
	return (sqrt(pow(x1 - game->p_x, 2) + pow(y1 - game->p_y, 2)));
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x > WIDTH || y > HEIGHT || y < 0 || x < 0)
		return ;
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	set_color(t_game *game)
{
	int	i;
	int	color;
	int	j;

	i = 0;
	color = mlx_get_color_value(game->mlx, 1991935);
	while (i < WIDTH)
	{
		j = 0;
		while (j < HEIGHT)
			my_mlx_pixel_put(game, i, j++, color);
		i++;
	}
}

void	move_w_s(int key, t_game *game, int n_x, int n_y)
{
	if (key == KEY_W)
	{
		n_x = floor((game->p_x + 4 * cos(game->rot_angle)));
		n_y = floor((game->p_y + 4 * sin(game->rot_angle)));
		if (wall_att(game, n_x, n_y))
		{
			game->p_x += 4.0 * cos(game->rot_angle);
			game->p_y += 4.0 * sin(game->rot_angle);
		}
	}
	else if (key == KEY_S)
	{
		n_x = floor((game->p_x - 4 * cos(game->rot_angle)));
		n_y = floor((game->p_y - 4 * sin(game->rot_angle)));
		if (wall_att(game, n_x, n_y))
		{
			game->p_x += -4.0 * cos(game->rot_angle);
			game->p_y += -4.0 * sin(game->rot_angle);
		}
	}
}

void	move_a_d(int key, t_game *game, int n_x, int n_y)
{
	if (key == KEY_A)
	{
		n_x = floor(game->p_x + 4 * sin(game->rot_angle));
		n_y = floor(game->p_y - 4 * cos(game->rot_angle));
		if (wall_att(game, n_x, n_y))
		{
			game->p_x += +4.0 * sin(game->rot_angle);
			game->p_y += -4.0 * cos(game->rot_angle);
		}
	}
	else if (key == KEY_D)
	{
		n_x = floor(game->p_x - 4 * sin(game->rot_angle));
		n_y = floor(game->p_y + 4 * cos(game->rot_angle));
		if (wall_att(game, n_x, n_y))
		{
			game->p_x += -4.0 * sin(game->rot_angle);
			game->p_y += +4.0 * cos(game->rot_angle);
		}
	}
}
