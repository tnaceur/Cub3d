/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:56:13 by tnaceur           #+#    #+#             */
/*   Updated: 2023/02/13 08:31:46 by tnaceur          ###   ########.fr       */
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
	mlx_hook(game.win, 17, 0, &ft_exit, NULL);
	mlx_hook(game.win, 2, 0, &key_press, &game);
	mlx_loop(game.mlx);
}
