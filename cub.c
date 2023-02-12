#include "cub.h"


typedef struct s_game	{
	void	*mlx;
	void	*win;
	void	*player;
	double	rot_angle;
	double		dir;
	double		p_x;
	double		p_y;
	int		width;
	int		height;
	int		red;
	int		black;
	int		white;
	int		fd;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F;
	char	*C;
	char	**map;
}	t_game;

int	str_2d(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char **map_read(t_game *game)
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
			break;
		if (line[0] == 'N' && line[1] == 'O')
			game->NO = line;
		else if (line[0] == 'S' && line[1] == 'O')
			game->SO = line;
		else if (line[0] == 'W' && line[1] == 'E')
			game->WE = line;
		else if (line[0] == 'E' && line[1] == 'A')
			game->EA = line;
		else if (line[0] == 'F')
			game->F = line;
		else if (line[0] == 'C')
			game->C = line;
		else if (line[0] == '\n' || line[0] == '\0')
			free(line);
		else if (line[0] == '1' || line[0] == '0' || line[0] == ' ')
			all_line = ft_strjoin(all_line, line);
		else
			printf("eoinfpm\n");
	}
	str = ft_split(all_line, '\n');
	free(line);
	free(all_line);
	return (str);
}


void	init_var(t_game *game, char *av)
{
	game->mlx = mlx_init();
	game->fd = open(av, O_RDONLY);
	game->map = map_read(game);
	if (game->map == NULL)
		exit(0);
	game->white = mlx_get_color_value(game->mlx, 16777215);
	game->red = mlx_get_color_value(game->mlx, 16711680);
	game->black = mlx_get_color_value(game->mlx,0);
	game->width = ft_strlen(game->map[0]) * 40;
	game->height = str_2d(game->map ) * 40;
	game->win= mlx_new_window(game->mlx, game->width, game->height, "cub3d");
	int i, j;
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

void	draw_line(t_game *game, int color)
{
	int		x2;
	int		y2;
	double	dx;
	double	dy;
	double	steps;
	double	xinc, yinc;
	double	x;
	double	y;

	// mlx_put_image_to_window(game->mlx, game->win, game->player, game->p_y, game->p_x);
	// draw_circle(game, game->p_y, game->p_x, 5, game->red);
	for (int i = game->p_x; i < game->p_x + 5; i++)
	{
		for (int j = game->p_y; j < game->p_y + 5; j++)
		{
			mlx_pixel_put(game->mlx, game->win, j, i, color);
		}
	}
	x2 = game->p_x + cos(game->rot_angle) * 30;
	y2 = game->p_y + sin(game->rot_angle) * 30;
	dx = x2 - game->p_x;
	dy = y2 - game->p_y;
	steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);
	xinc = dx / steps;
	yinc = dy / steps;
	x = game->p_x;
	y = game->p_y;
	for (int i = 0; i <= steps; i++)
	{
		mlx_pixel_put(game->mlx, game->win, y, x, color);
		x += xinc;
		y += yinc;
	}
}

int ft()
{
	exit(0);
}

int	key_press(int key, t_game *game)
{
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
		int	n_x = floor((game->p_x + 4 * cos(game->rot_angle)));
		int	n_y = floor((game->p_y + 4 * sin(game->rot_angle)));
		if (game->map[n_x / 40][n_y / 40] != '1')
		{
			draw_line(game, game->black);
			game->p_x += 4.0 * cos(game->rot_angle);
			game->p_y += 4.0 * sin(game->rot_angle);
		}
	}
	else if (key == 1)
	{
		int	n_x = floor((game->p_x - 4 * cos(game->rot_angle)) );
		int	n_y = floor((game->p_y - 4 * sin(game->rot_angle)));
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
	int i;
	int	j;
	int	a;
	int	b;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		a = i * 40;
		while (game->map[i][j])
		{
			for (int s = 0; s < 40; s++)
			{
				b = j * 40;
				for (int c = 0; c < 40; c++)
				{
					mlx_pixel_put(game->mlx, game->win, b, a, game->black);
					b++;
				}
				a++;
			}
			a = i * 40;
			if (game->map[i][j] == '1')
			{
				for (int s = 0; s < 40; s++)
				{
					b = j * 40;
					for (int c = 0; c < 40; c++)
					{
						mlx_pixel_put(game->mlx, game->win, b, a, game->white);
						b++;
					}
					a++;
				}
				a = i * 40;
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
