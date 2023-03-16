/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:30:26 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/06 15:06:00 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_mprint(char **str)
{
	int	i;

	i = 0;
	if (!str)
		ft_put_error(" mprint \n");
	printf("\n\n<<<<<<<<< start print 2d >>>>>>>>>\n\n");
	while (str[i])
		printf("<[ |%s| ]>\n", str[i++]);
	printf("\n\n<<<<<<<<< stop  print 2d >>>>>>>>>\n\n");
}

void	ft_print_struct(t_pdata *data, char *msg)
{
	if (!data)
		ft_put_error("ft_print_struct");
	printf("\n\n<<<<<<<<<< start print struct members >>>>>>>>>>>>>");
	printf("\n<<<<<<<<<< [%s] >>>>>>>>>>>>>\n\n", msg);
	printf("north <[%s]> \n", data->north_t);
	printf("south <[%s]> \n", data->south_t);
	printf("west  <[%s]> \n", data->west_t);
	printf("east  <[%s]> \n", data->east_t);
	if (data->rgb_f || data->rgb_c)
	{
		printf("color_f = %d | rgb_f <[ %d | %d | %d ]>\n", data->col_f, \
			data->rgb_f[0], data->rgb_f[1], data->rgb_f[2]);
		printf("color_c = %d | rgb_c <[ %d | %d | %d ]>\n", data->col_c, \
			data->rgb_c[0], data->rgb_c[1], data->rgb_c[2]);
	}
	else
		ft_put_error("rgb address");
	printf("map  == <[%s]>\n", data->map->mapline);
	printf("\n\n<<<<<<<<<<<<<<<<<< stop print >>>>>>>>>>>>>>>>>>>>\n\n");
}

void	ft_tprint(char **str, int _y, int _x)
{
	int	x;
	int	y;

	x = -1;
	y = 0;
	printf("[X] ");
	while (str[0][++x])
		printf("[%d] ", x);
	printf("\n----------------------------------------------------------\n");
	while (str[y])
	{
		x = -1;
		printf("[%d] ", y);
		while (str[y][++x])
		{
			if (y == _y && x == _x)
				printf("\033[0;31m");
			printf(" %c  ", str[y][x]);
			if (y == _y && x == _x)
				printf("\033[0m");
		}
		printf("\n----------------------------------------------------------\n");
		y++;
	}
}
