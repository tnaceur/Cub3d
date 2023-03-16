/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:56:13 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/16 22:24:59 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	draw_rays(t_game *game, int color)
{
	int		i;
	double	ray;
	double	corr_dst;
	double	dst_proj_wall;
	double	wall_high;

	ray = game->rot_angle - (game->fov / 2);
	i = 0;
	while (i < WIDTH)
	{
		ray = fmod(ray, (2 * M_PI));
		if (ray < 0)
			ray = (2 * M_PI) + ray;
		draw_line(game, ray, color, 500);
		corr_dst = game->dst * cos(ray - game->rot_angle);
		dst_proj_wall = (WIDTH / 2) / tan(game->fov / 2);
		wall_high = (40 / corr_dst) * dst_proj_wall;
		d_wall_3d(game, (HEIGHT / 2) - wall_high / 2, i, wall_high);
		ray += game->fov / WIDTH;
		i++;
	}
}

int	render(t_game *game)
{
	int	a;

	mlx_destroy_image(game->mlx, game->img);
	mlx_clear_window(game->mlx, game->win);
	game->img = mlx_xpm_file_to_image(game->mlx, "./texture/sr.xpm", &a, &a);
	if (!game->img)
		ft_put_error("game->add mlx_new_image  failed");
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
		ft_put_error("game->add mlx_get_addr  failed");
	draw_rays(game, game->red);
	put_player(game, 1703705);
	draw_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

int	key_press(int key, t_game *game)
{
	move_w_s(key, game, 0, 0);
	move_a_d(key, game, 0, 0);
	if (key == KEY_LEFT)
	{
		game->dir = -1;
		game->rot_angle += game->dir * 6 * (M_PI / 180);
	}
	else if (key == KEY_RIGHT)
	{
		game->dir = 1;
		game->rot_angle += game->dir * 6 * (M_PI / 180);
	}
	else if (key == 53)
		exit(0);
	render(game);
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_pdata	*data;

	data = (t_pdata *)malloc(sizeof(t_pdata));
	if (!data)
		ft_put_error("malloc faile (main)");
	ft_init_struct(data);
	ft_check_error(ac, av[1], data);
	ft_init_game(&game, data);
	draw_map(&game);
	if (data->map->o == 'N')
		game.rot_angle = M_PI;
	else if (data->map->o == 'E')
		game.rot_angle = M_PI / 2;
	else if (data->map->o == 'S')
		game.rot_angle = 2 * M_PI;
	else if (data->map->o == 'W')
		game.rot_angle = 3 * M_PI / 2;
	mlx_hook(game.win, 17, 0, ft_exit, NULL);
	render(&game);
	mlx_hook(game.win, 2, 0, key_press, &game);
	mlx_loop(game.mlx);
}
