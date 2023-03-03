/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:24:42 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/03 15:48:10 by tnaceur          ###   ########.fr       */
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
