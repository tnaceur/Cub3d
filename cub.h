/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:47:03 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/03 18:58:43 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define WIDTH 1008
# define HEIGHT 600
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_RIGHT 124
# define KEY_LEFT 123

# include "libft/libft.h"
# include <stdio.h>
# include <mlx.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_game {
	void	*mlx;
	void	*win;
	void	*img;
	void	*player;
	double	rot_angle;
	double	fov;
	double	dir;
	double	p_x;
	double	p_y;
	double	dst;
	double	ray;
	int		n_x;
	int		n_y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		red;
	int		black;
	int		bl;
	int		fd;
	int		hieght;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	*addr;
	char	**map;
	int 	face;
}	t_game;

typedef struct s_line {
	double	x2;
	double	y2;
	int		face;
	double	dx;
	double	dy;
	double	steps;
	double	xinc;
	double	yinc;
	int		i;
	int		j;
}	t_line;

char	*get_next_line(int fd);
char	**map_read(t_game *game);
int		str_2d(char **s);
int		map_name(char *av2);
int		ft_exit(void);
void	init_var(t_game *game, char *av);
void	draw_line(t_game *game, double angle, int color, int tall);
void	draw_map(t_game *game);
void	put_player(t_game *game, int color);
int		my_mlx_pixel_put(t_game *game, int x, int y, int color);
double	distance(t_game *game, double x1, double y1);
void	d_wall_3d(t_game *game, double x, double y, double height);
void	move_w_s(int key, t_game *game, int n_x, int n_y);
void	move_a_d(int key, t_game *game, int n_x, int n_y);
int		wall_att(t_game *game, double x2, double y2);
int		player_pos(t_game *game, double x2, double y2);

#endif
