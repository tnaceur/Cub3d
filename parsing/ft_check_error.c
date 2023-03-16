/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:28:50 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/06 20:13:14 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	ft_check_data(char **str)
{
	int	i;
	int	start;
	int	v;
	int	mlen;

	i = 0;
	v = 0;
	mlen = ft_mlen(str);
	while (str[i])
	{
		start = 0;
		ft_bypass_char(str[i], &start, ' ', 0);
		if (start == ft_len(str[i]))
			v++;
		i++;
	}
	if (mlen > 0 && mlen <= 6 && mlen != v)
		ft_put_error("Incomplite data");
	if (mlen == 0 || v == mlen)
		ft_put_error("No data found");
	return (true);
}

void	ft_check_error_helper(t_pdata *data)
{
	int	i;

	i = -1;
	ft_check_xpm(data);
	while (++i < 3)
		if (data->rgb_c[i] == -1 || data->rgb_f[i] == -1)
			ft_put_error("invalid rgb data");
	data->col_c = (data->rgb_c[0] << 16 | data->rgb_c[1] << 8 | data->rgb_c[2]);
	data->col_f = (data->rgb_f[0] << 16 | data->rgb_f[1] << 8 | data->rgb_f[2]);
	ft_check_map(data);
}

void	ft_check_error(int ac, char *av, t_pdata *data)
{
	int	fd;

	if (ac != 2 || !av)
		ft_put_error("You need to add map file");
	if (!ft_check_ext(av, ".cub"))
		ft_put_error("Invalide extension");
	fd = open(av, 0);
	if (fd == -1)
		ft_put_error("Open failed");
	data->full_map = ft_read_mapfile(fd);
	if (!ft_len(data->full_map))
		ft_put_error("Empty file");
	data->map_file = ft_strsplit(data->full_map, '\n');
	if (!data->map_file)
		ft_put_error("Split failed");
	ft_check_data(data->map_file);
	ft_fill_struct(data);
	ft_check_error_helper(data);
}
