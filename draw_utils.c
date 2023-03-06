/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 09:38:18 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/06 09:46:31 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_color(t_img *tswira, int y, int x)
{
	int	*color;

	if (y >= tswira->width || y >= tswira->height || y < 0 || x < 0)
		return (0);
	color = (int *)(tswira->addr + (y * tswira->line_length
				+ x * (tswira->bits_per_pixel / 8)));
	return (*color);
}

void	celling(t_game *game, t_3d *dr)
{
	dr->a = 0;
	dr->b = 0;
	dr->color = 0xD2DCFF;
	while (dr->x >= 0 && dr->a < HEIGHT && dr->a < dr->x)
	{
		dr->b = dr->y;
		if (dr->a > HEIGHT)
			break ;
		if (dr->b < WIDTH && dr->b < dr->y + 1)
		{
			my_mlx_pixel_put(game, dr->b, dr->a, dr->color);
			dr->b++;
		}
		dr->a++;
	}
}

void	flr(t_game *game, t_3d *dr)
{
	dr->color = 0xffffff;
	dr->a = dr->x + dr->w_height;
	while (dr->a > 0 && dr->a < HEIGHT)
	{
		dr->b = dr->y;
		if (dr->a > HEIGHT)
			break ;
		while (dr->b < WIDTH && dr->b < dr->y + 1)
		{
			if (my_mlx_pixel_put(game, dr->b, dr->a, dr->color))
				dr->b++ ;
			else
				break ;
		}
		dr->a++;
	}
}

void	init_faces(t_game *game, t_img *tswira, t_3d *dr)
{
	while (dr->i < HEIGHT && dr->i <= dr->x + dr->w_height)
	{
		dr->j = dr->y;
		if (dr->i > HEIGHT)
			break ;
		dr->xx = (dr->i - dr->x) * ((float)tswira->height / dr->w_height);
		if (dr->j < WIDTH && dr->j <= dr->y + 1)
		{
			if (!my_mlx_pixel_put(game, dr->j + 1, dr->i,
					get_color(tswira, dr->xx, dr->offset_x)))
				break ;
		}
		dr->i++;
	}
}

void	d_wall_3d(t_game *game, double x, double y, double w_height)
{
	t_3d	dr;
	t_img	tswira;

	dr.x = x;
	dr.y = y;
	celling(game, &dr);
	if (game->face == 1 || game->face == 2)
		dr.offset_x = (int)game->wall_hity % 40;
	else
		dr.offset_x = (int)game->wall_hitx % 40;
	if (game->face == 1)
		tswira = game->texture;
	else if (game->face == 2)
		tswira = game->texture1;
	else if (game->face == 3)
		tswira = game->texture2;
	else if (game->face == 4)
		tswira = game->texture3;
	dr.i = x;
	if (dr.i < 0)
		dr.i = 0;
	dr.xx = 0;
	dr.w_height = w_height;
	init_faces(game, &tswira, &dr);
	flr(game, &dr);
}
