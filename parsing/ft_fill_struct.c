/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 16:37:42 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/08 10:19:54 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_get_data(char **str, char *sch, int lo)
{
	int		i;
	char	*tmp;
	int		v;

	i = 0;
	v = 0;
	if (!str)
		ft_put_error("get_data");
	tmp = NULL;
	while (str[i] && i < lo)
	{
		if (ft_strstr(str[i], sch))
		{
			tmp = ft_dup(str[i]);
			v++;
		}
		i++;
	}
	if (v == 1)
		return (tmp);
	free(tmp);
	return (NULL);
}

void	ft_init_pmap(t_pdata *data)
{
	if (!data)
		ft_put_error("data ft_init_pmap");
	data->map = (t_pmap *)malloc(sizeof(t_pmap));
	if (!data->map)
		ft_put_error("tmp ft_init_pmap");
	data->map->mapline = NULL;
	data->map->map = NULL;
	data->map->basic_map = NULL;
	data->map->len = 0;
	data->map->mlen = 0;
	data->map->o = 0;
}

void	ft_init_struct(t_pdata *data)
{
	int	i;

	data->full_map = NULL;
	data->map_file = NULL;
	data->north_t = NULL;
	data->south_t = NULL;
	data->west_t = NULL;
	data->east_t = NULL;
	ft_init_pmap(data);
	data->col_c = -1;
	data->col_f = -1;
	data->rgb_f = (int *)malloc(sizeof(int) * 3);
	data->rgb_c = (int *)malloc(sizeof(int) * 3);
	i = -1;
	while (++i < 3)
		data->rgb_c[i] = (data->rgb_f[i] = -1);
}

int	ft_first_parte(char **str)
{
	int	i;
	int	v;

	if (!str)
		ft_put_error("str");
	i = 0;
	v = 0;
	while (str[i])
	{
		if (ft_strstr(str[i], "NO") || ft_strstr(str[i], "SO")
			|| ft_strstr(str[i], "WE") || ft_strstr(str[i], "EA")
			|| ft_strstr(str[i], "F") || ft_strstr(str[i], "C"))
			v++;
		else if (ft_sch(str[i], ' '))
			v++;
		else
			return (v);
		i++;
	}
	return (v);
}

void	ft_fill_struct(t_pdata *data)
{
	char	*tmp;
	int		i;

	if (!data || !data->map_file)
		ft_put_error("address (ft_get_map)");
	i = ft_first_parte(data->map_file);
	data->north_t = ft_get_data(data->map_file, "NO", i);
	data->south_t = ft_get_data(data->map_file, "SO", i);
	data->west_t = ft_get_data(data->map_file, "WE", i);
	data->east_t = ft_get_data(data->map_file, "EA", i);
	tmp = ft_get_data(data->map_file, "F", i);
	ft_get_rgb(tmp, data, 'F');
	free(tmp);
	tmp = ft_get_data(data->map_file, "C", i);
	ft_get_rgb(tmp, data, 'C');
	free(tmp);
}
