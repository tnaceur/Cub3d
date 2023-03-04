/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:56:13 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/04 12:52:32 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	**map_read(t_game *game)
{
	char	*all_line;
	char	**str;
	char	*line;

	if (game->fd < 0)
		exit(write(2, "Error : Infile cannot be opened\n", 32) - 31);
	all_line = NULL;
	while (1)
	{
		line = get_next_line(game->fd);
		if (line == NULL)
			break ;
		if (line[0] == 'N' && line[1] == 'O')
			game->no = line;
		else if (line[0] == 'S' && line[1] == 'O')
			game->so = line;
		else if (line[0] == 'W' && line[1] == 'E')
			game->we = line;
		else if (line[0] == 'E' && line[1] == 'A')
			game->ea = line;
		else if (line[0] == 'F')
			game->f = line;
		else if (line[0] == 'C')
			game->c = line;
		else if (line[0] == '\n' || line[0] == '\0')
			free(line);
		else if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
			all_line = ft_strjoin(all_line, line);
		else
			exit(write(2, "Error\n", 6) - 5);
	}
	str = ft_split(all_line, '\n');
	free(line);
	free(all_line);
	return (str);
}

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
		draw_line(game, ray, color, INT_MAX);
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
	mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	draw_rays(game, game->red);
	put_player(game, 65380);
	draw_line(game, game->rot_angle, 65380, 100);
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

	if (ac != 2 || !map_name(av[1]))
		exit(write(2, "Error\n", 6) - 5);
	init_var(&game, av[1]);
	draw_map(&game);
	game.texture.img = mlx_xpm_file_to_image(game.mlx, "zelij.xpm", &game.texture.width, &game.texture.height);
	game.texture.addr = mlx_get_data_addr(game.texture.img, &game.texture.bits_per_pixel, &game.texture.line_length, &game.texture.endian);
	if (game.map[(int)(game.p_x / 40)][(int)(game.p_y / 40)] == 'N')
		game.rot_angle = M_PI;
	else if (game.map[(int)(game.p_x / 40)][(int)(game.p_y / 40)] == 'E')
		game.rot_angle = M_PI / 2;
	else if (game.map[(int)(game.p_x / 40)][(int)(game.p_y / 40)] == 'S')
		game.rot_angle = 2 * M_PI;
	else if (game.map[(int)(game.p_x / 40)][(int)(game.p_y / 40)] == 'W')
		game.rot_angle = 3 * M_PI / 2;
	mlx_hook(game.win, 17, 0, ft_exit, NULL);
	render(&game);
	mlx_hook(game.win, 2, 0, key_press, &game);
	mlx_loop(game.mlx);
}
