/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:24:42 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/16 22:24:08 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_exit(void)
{
	exit(0);
}

void	ft_init_textures_help(t_game *game)
{
	game->texture.addr = mlx_get_data_addr(game->texture.img, \
		&game->texture.bits_per_pixel, &game->texture.line_length, \
		&game->texture.endian);
	game->texture1.addr = mlx_get_data_addr(game->texture1.img, \
		&game->texture1.bits_per_pixel, &game->texture1.line_length, \
		&game->texture1.endian);
	game->texture2.addr = mlx_get_data_addr(game->texture2.img, \
		&game->texture2.bits_per_pixel, &game->texture2.line_length, \
		&game->texture2.endian);
	game->texture3.addr = mlx_get_data_addr(game->texture3.img, \
		&game->texture3.bits_per_pixel, &game->texture3.line_length, \
		&game->texture3.endian);
	if (!game->texture.addr || !game->texture1.addr || !game->texture2.addr
		|| !game->texture3.addr)
		ft_put_error("Invalid content of XPM file (mlx_get_data_addr failed)");
}

void	ft_init_textures(t_game *game, t_pdata *data)
{
	game->texture.img = mlx_xpm_file_to_image(game->mlx, data->north_t,
			&game->texture.width, &game->texture.height);
	game->texture1.img = mlx_xpm_file_to_image(game->mlx, data->west_t,
			&game->texture1.width, &game->texture1.height);
	game->texture2.img = mlx_xpm_file_to_image(game->mlx, data->south_t,
			&game->texture2.width, &game->texture2.height);
	game->texture3.img = mlx_xpm_file_to_image(game->mlx, data->east_t,
			&game->texture3.width, &game->texture3.height);
	if (!game->texture.img || !game->texture1.img || !game->texture2.img
		|| !game->texture3.img)
		ft_put_error("Invalid XPM file (mlx_xpm_file_to_image failed)");
	ft_init_textures_help(game);
}

void	ft_init_game(t_game *game, t_pdata *data)
{
	game->map = data->map->basic_map;
	game->hieght = data->map->mlen;
	game->mlx = mlx_init();
	if (!game->mlx)
		ft_put_error("mlx_init failed");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!game->win)
		ft_put_error("mlx_new_windows failed");
	game->bl = mlx_get_color_value(game->mlx, 16777215);
	game->red = mlx_get_color_value(game->mlx, 16711680);
	ft_init_textures(game, data);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->bl || !game->red || !game->img)
		ft_put_error("bl or red or img (mlx_get_color or mlx_get_data failed)");
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
		ft_put_error("game->add mlx_get_addr  failed");
	game->fov = 60 * (M_PI / 180);
	game->p_x = 0;
	game->p_y = 0;
	game->f = data->col_f;
	game->c = data->col_c;
}
