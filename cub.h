/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnaceur <tnaceur@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 01:47:03 by tnaceur           #+#    #+#             */
/*   Updated: 2023/02/17 09:14:32 by tnaceur          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define HIGHT 420
# define WIDTH 1080

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
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		red;
	int		black;
	int		bl;
	int		fd;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	char	*addr;
	char	**map;
}	t_game;

typedef struct s_line {
	double	x2;
	double	y2;
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
void	draw_line(t_game *game, double angle, int color);
void	draw_map(t_game *game);
void	put_player(t_game *game, int color);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);

#endif
