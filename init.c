/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 08:24:42 by tnaceur           #+#    #+#             */
/*   Updated: 2023/02/17 08:57:55 by tnaceur          ###   ########.fr       */
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
	game->bl = mlx_get_color_value(game->mlx, 16777215);
	game->red = mlx_get_color_value(game->mlx, 16711680);
	game->black = mlx_get_color_value(game->mlx, 0);
	game->width = ft_strlen(game->map[0]) * 40;
	game->height = str_2d(game->map) * 40;
	game->win = mlx_new_window(game->mlx, game->width, game->height, "cub3d");
	game->player = mlx_xpm_file_to_image(game->mlx, "p_right.xpm", &i, &j);
	game->fov = 60 * (M_PI / 180);
	game->p_x = 0;
	game->p_y = 0;
	game->img = mlx_new_image(game->mlx, game->width, game->height);
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

void	draw_line(t_game *game, double angle, int color)
{
	t_line	line;

	line.x2 = game->p_x + cos(angle) * INT_MAX;
	line.y2 = game->p_y + sin(angle) * INT_MAX;
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
	while (++line.i <= line.steps)
	{
		if (game->map[(int)floor(line.x2 / 40)]
			[(int)floor(line.y2 / 40)] == '1')
			break ;
		my_mlx_pixel_put(game, round(line.y2), round(line.x2), color);
		line.x2 += line.xinc;
		line.y2 += line.yinc;
	}
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
	while (i < game->p_x + 5)
	{
		j = game->p_y;
		while (j < game->p_y + 5)
			my_mlx_pixel_put(game, j++, i, color);
		i++;
	}
}
