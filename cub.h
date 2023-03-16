/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:47:03 by tnaceur           #+#    #+#             */
/*   Updated: 2023/03/16 22:21:00 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define WIDTH 1280
# define HEIGHT 720
# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define KEY_RIGHT 124
# define KEY_LEFT 123

# include "parsing/parsing.h"
# include <stdio.h>
# include <mlx.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_3d {
	double	i;
	double	xx;
	double	x;
	double	y;
	double	w_height;
	double	j;
	int		a;
	int		offset_x;
	int		b;
	int		color;
}	t_3d;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_game {
	t_img	texture;
	t_img	texture1;
	t_img	texture2;
	t_img	texture3;
	void	*mlx;
	void	*win;
	void	*img;
	void	*scy;
	double	rot_angle;
	double	fov;
	double	dir;
	double	p_x;
	double	p_y;
	double	dst;
	double	ray;
	double	wall_hitx;
	double	wall_hity;
	int		n_x;
	int		n_y;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		red;
	int		bl;
	int		hieght;
	int		f;
	int		c;
	char	*addr;
	char	**map;
	int		face;
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

char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *str);

void	ft_init_textures(t_game *game, t_pdata *data);
void	ft_init_game(t_game *game, t_pdata *data);
int		ft_exit(void);
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
