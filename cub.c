/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:56:13 by tnaceur           #+#    #+#             */
/*   Updated: 2023/02/13 08:20:30 by tnaceur          ###   ########.fr       */
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

void	put_player(t_game *game, t_line *line, int color)
{
	line->i = game->p_x;
	while (line->i < game->p_x + 5)
	{
		line->j = game->p_y;
		while (line->j < game->p_y + 5)
			mlx_pixel_put(game->mlx, game->win, line->j++, line->i, color);
		line->i++;
	}
}

void	draw_line(t_game *game, int color)
{
	t_line	line;

	put_player(game, &line, color);
	line.x2 = game->p_x + cos(game->rot_angle) * 30;
	line.y2 = game->p_y + sin(game->rot_angle) * 30;
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
		mlx_pixel_put(game->mlx, game->win, line.y2, line.x2, color);
		line.x2 += line.xinc;
		line.y2 += line.yinc;
	}
}

int	ft(void)
{
	exit(0);
}

int	key_press(int key, t_game *game)
{
	int	n_x;
	int	n_y;

	if (key == 124)
	{
		draw_line(game, game->black);
		game->dir = -1;
		game->rot_angle += game->dir * 6 * (acos(-1) / 180);
	}
	else if (key == 123)
	{
		draw_line(game, game->black);
		game->dir = 1;
		game->rot_angle += game->dir * 6 * (acos(-1) / 180);
	}
	else if (key == 13)
	{
		n_x = floor((game->p_x + 4 * cos(game->rot_angle)));
		n_y = floor((game->p_y + 4 * sin(game->rot_angle)));
		if (game->map[n_x / 40][n_y / 40] != '1')
		{
			draw_line(game, game->black);
			game->p_x += 4.0 * cos(game->rot_angle);
			game->p_y += 4.0 * sin(game->rot_angle);
		}
	}
	else if (key == 1)
	{
		n_x = floor((game->p_x - 4 * cos(game->rot_angle)));
		n_y = floor((game->p_y - 4 * sin(game->rot_angle)));
		if (game->map[n_x / 40][n_y / 40] != '1')
		{
			draw_line(game, game->black);
			game->p_x += -4.0 * cos(game->rot_angle);
			game->p_y += -4.0 * sin(game->rot_angle);
		}
	}
	else if (key == 53)
		exit(0);
	return (0);
}

int	render(t_game *game)
{
	draw_line(game, game->red);
	return (0);
}

void	draw_map(t_game *game)
{
	int	i;
	int	j;
	int	s;
	int	c;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == '1')
			{
				s = i * 40;
				while (s < (i * 40) + 40)
				{
					c = j * 40;
					while (c < (j * 40) + 40)
						mlx_pixel_put(game->mlx, game->win, c++, s, game->bl);
					s++;
				}
			}
			else if (game->map[i][j] == 'N' || game->map[i][j] == 'S'
				|| game->map[i][j] == 'W' || game->map[i][j] == 'E')
			{
				game->p_x = i * 40;
				game->p_y = j * 40;
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2 || !map_name(av[1]))
		exit(write(2, "Error\n", 6) - 5);
	init_var(&game, av[1]);
	draw_map(&game);
	if (game.map[(int)(game.p_x / 40)][(int)(game.p_y / 40)] == 'N')
		game.rot_angle = acos(-1);
	else if (game.map[(int)(game.p_x / 40)][(int)(game.p_y / 40)] == 'E')
		game.rot_angle = acos(-1) / 2;
	else if (game.map[(int)(game.p_x / 40)][(int)(game.p_y / 40)] == 'S')
		game.rot_angle = 2 * acos(-1);
	else if (game.map[(int)(game.p_x / 40)][(int)(game.p_y / 40)] == 'W')
		game.rot_angle = 3 * acos(-1) / 2;
	mlx_loop_hook(game.mlx, &render, &game);
	mlx_hook(game.win, 17, 0, &ft, NULL);
	mlx_hook(game.win, 2, 0, &key_press, &game);
	mlx_loop(game.mlx);
}
