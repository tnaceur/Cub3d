/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 09:13:46 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/05 16:06:56 by tnaceur          ###   ########.fr       */
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

int	wall_att(t_game *game, double x2, double y2)
{
	int	x;
	int	y;

	x = floor(x2 / 40);
	y = floor(y2 / 40);
	if (x > 0 && y > 0 && game->map[x] && game->map[x][y] != '1')
		return (1);
	// x = floor((x2 + 1) / 40);
	// y = floor(y2 / 40);
	// if (x >= 0 && y >= 0 && game->map[x] && game->map[x][y] == '1')
	// {
	// 	puts("herre");
	// 	return (0);
	// }
	// x = floor(x2 / 40);
	// y = floor((y2 + 1) / 40);
	// if (x >= 0 && y >= 0 && game->map[x] && game->map[x][y] == '1')
	// {
	// 	puts("herre1");
	// 	return (0);
	// }
	// x = floor((x2 - 1) / 40);
	// y = floor(y2 / 40);
	// if (x >= 0 && y >= 0 && game->map[x] && game->map[x][y] == '1')
	// {
	// 	puts("herre2");
	// 	return (0);
	// }
	// x = floor(x2 / 40);
	// y = floor((y2 - 1) / 40);
	// if (x >= 0 && y >= 0 && game->map[x] && game->map[x][y] == '1')
	// {
	// 	puts("herre3");
	// 	return (0);
	// }
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

void	draw_line(t_game *game, double angle, int color, int tall)
{
	t_line	line;
	double	x_step;
	double	y_step;

	line.x2 = game->p_x;
	line.y2 = game->p_y;
	(void)tall;
	x_step = cos(angle);
	y_step = sin(angle);
	while (wall_att(game, line.x2, line.y2))
	{
		my_mlx_pixel_put(game, line.y2 * 0.1,
			line.x2 * 0.1, color);
		if (!wall_att(game, line.x2 + x_step, line.y2))
		{
			line.x2 += x_step;
			if (x_step > 0)
				game->face = 1;
			else
				game->face = 2;
			break ;
		}
		if (!wall_att(game, line.x2, line.y2 + y_step))
		{
			line.y2 += y_step;
			if (y_step > 0)
				game->face = 3;
			else
				game->face = 4;
			break ;
		}
		line.x2 += x_step;
		line.y2 += y_step;
	}
	game->wall_hitx = line.x2;
	game->wall_hity = line.y2;
	game->dst = distance(game, line.x2, line.y2);
}

int get_color(t_img *tswira, int y, int x)
{
    int *color;

	if (y >= tswira->width || y >= tswira->height || y < 0 || x < 0)
		return (0);
    color = (int *) (tswira->addr + (y * tswira->line_length + x * (tswira->bits_per_pixel / 8)));
    return (*color);
}

void	d_wall_3d(t_game *game, double x, double y, double w_height)
{
	double	i;
	double	j;
	int		a;
	int		b;
	int		color;
	t_img	tswira;

	a = 0;
	b = 0;
	color = 0xD2DCFF;
	while (x >= 0 && a < HEIGHT && a < x)
	{
		b = y;
		if (a > HEIGHT)
			break ;
		while (b < WIDTH && b < y + 1)
		{
			my_mlx_pixel_put(game, b, a, color);
			b++;
		}
		a++;
	}
	int	offset_x;
	if (game->face == 1 || game->face == 2)
		offset_x = (int)game->wall_hity % 40;
	else
		offset_x = (int)game->wall_hitx % 40;
	if (game->face == 1)
		tswira = game->texture;
		// color = 0xff0000;
	else if (game->face == 2)
		tswira = game->texture1;
		// color = 0x00ffff;
	else if (game->face == 3)
		tswira = game->texture2;
		// color = 0xffff00;
	else if (game->face == 4)
		tswira = game->texture3;
		// color = 0x0000ff;
	i = x;
	if (i < 0)
		i = 0;
	double	xx;
	xx = 0;
	while (i < HEIGHT && i <= x + w_height)
	{
		j = y;
		if (i > HEIGHT)
			break ;
		xx = (i - x) * ((float)tswira.height / w_height);
		if (j < WIDTH && j <= y + 1)
		{
			my_mlx_pixel_put(game, j + 1, i, get_color(&tswira, xx, offset_x));
		}
		i++;
	}
	color = 0xffffff;
	a = x + w_height;
	while (a > 0 && a < HEIGHT)
	{
		b = y;
		if (a > HEIGHT)
			break ;
		while (b < WIDTH && b < y + 1)
		{
			if (my_mlx_pixel_put(game, b, a, color))
				b++ ;
			else
				break ;
		}
		a++;
	}
}
