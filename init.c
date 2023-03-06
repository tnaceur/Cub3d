/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:24:42 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/06 09:42:37 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	str_2d(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	init_textures(t_game *game)
{
	game->texture.img = mlx_xpm_file_to_image(game->mlx, "texture/Laava.xpm",
			&game->texture.width, &game->texture.height);
	game->texture.addr
		= mlx_get_data_addr(game->texture.img, &game->texture.bits_per_pixel,
			&game->texture.line_length, &game->texture.endian);
	game->texture1.img = mlx_xpm_file_to_image(game->mlx, "texture/w2.xpm",
			&game->texture1.width, &game->texture1.height);
	game->texture1.addr
		= mlx_get_data_addr(game->texture1.img, &game->texture1.bits_per_pixel,
			&game->texture1.line_length, &game->texture1.endian);
	game->texture2.img = mlx_xpm_file_to_image(game->mlx, "texture/w3.xpm",
			&game->texture2.width, &game->texture2.height);
	game->texture2.addr
		= mlx_get_data_addr(game->texture2.img, &game->texture2.bits_per_pixel,
			&game->texture2.line_length, &game->texture2.endian);
	game->texture3.img = mlx_xpm_file_to_image(game->mlx, "texture/w4.xpm",
			&game->texture3.width, &game->texture3.height);
	game->texture3.addr
		= mlx_get_data_addr(game->texture3.img, &game->texture3.bits_per_pixel,
			&game->texture3.line_length, &game->texture3.endian);
}

void	init_var(t_game *game, char *av)
{
	int	i;
	int	j;

	game->mlx = mlx_init();
	game->fd = open(av, O_RDONLY);
	game->map = map_read(game);
	if (game->map == NULL)
		exit(0);
	game->hieght = str_2d(game->map);
	game->bl = mlx_get_color_value(game->mlx, 16777215);
	game->red = mlx_get_color_value(game->mlx, 16711680);
	game->black = mlx_get_color_value(game->mlx, 0);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	game->player = mlx_xpm_file_to_image(game->mlx, "p_right.xpm", &i, &j);
	game->fov = 60 * (M_PI / 180);
	game->p_x = 0;
	game->p_y = 0;
	init_textures(game);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
}

int	map_name(char *av2)
{
	int		i;
	int		j;
	char	*str;

	str = ".cub";
	i = 0;
	while (av2[i])
		i++;
	j = 0;
	i -= 4;
	while (str[j] == av2[i] && av2[i] && str[j])
	{
		i++;
		j++;
	}
	if (str[j] == av2[i])
		return (1);
	return (0);
}

int	ft_exit(void)
{
	exit(0);
}
