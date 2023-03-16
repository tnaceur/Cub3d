/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xpm.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:13:46 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/07 16:26:53 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_check_xpm_help1(char *str, char *sch)
{
	char	*tmp;
	int		start;
	int		end;

	start = 0;
	end = 0;
	if (!str)
		ft_put_error("str ft_check_xpm_help");
	while (str[start] && str[start] == ' ')
		start++;
	end = start;
	while (str[end] && str[end] != ' ')
		end++;
	tmp = ft_sub(str, start, end - start);
	if (!tmp)
		ft_put_error("1 tmp ft_check_xpm_help");
	if (!ft_cmp(tmp, sch))
		end = -1;
	free(tmp);
	return (end);
}

bool	ft_open_xpm(char **str, char *tmp)
{
	int	fd;

	if (!ft_check_ext(tmp, ".xpm"))
		return (false);
	fd = open(tmp, O_RDONLY);
	if (fd != -1)
	{
		close(fd);
		free(*str);
		*str = ft_dup(tmp);
		return (true);
	}
	return (false);
}

bool	ft_check_xpm_help(char **str, char *sch)
{
	char	*tmp;
	int		start;
	int		end;
	bool	valid;

	start = ft_check_xpm_help1(*str, sch);
	if (start <= 0 || start >= ft_len(*str))
		return (false);
	ft_bypass_char(*str, &start, ' ', 0);
	end = ft_len(*str) - 1;
	ft_bypass_char(*str, &end, ' ', 1);
	tmp = ft_sub(*str, start, end - start + 1);
	if (!tmp)
		ft_put_error("2 tmp ft_check_xpm_help");
	valid = ft_open_xpm(str, tmp);
	free(tmp);
	return (valid);
}

void	ft_check_xpm(t_pdata *data)
{
	if (!data)
		ft_put_error("data ft_check_xpm ");
	if (!data->north_t || !ft_check_xpm_help(&data->north_t, "NO"))
		ft_put_error("Invalid texture NO");
	if (!data->south_t || !ft_check_xpm_help(&data->south_t, "SO"))
		ft_put_error("Invalid texture SO");
	if (!data->west_t || !ft_check_xpm_help(&data->west_t, "WE"))
		ft_put_error("Invalid texture WE");
	if (!data->east_t || !ft_check_xpm_help(&data->east_t, "EA"))
		ft_put_error("Invalid texture EA");
}
