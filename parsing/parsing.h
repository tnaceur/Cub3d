/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelkhad <abelkhad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 11:16:55 by abelkhad          #+#    #+#             */
/*   Updated: 2023/03/08 10:05:57 by abelkhad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_pmap
{
	char	*mapline;
	char	**map;
	char	**basic_map;
	int		len;
	int		mlen;
	char	o;

}			t_pmap;

typedef struct s_pdata
{
	int		*rgb_c;
	int		*rgb_f;
	int		col_c;
	int		col_f;
	t_pmap	*map;
	char	*full_map;
	char	**map_file;
	char	*north_t;
	char	*south_t;
	char	*west_t;
	char	*east_t;
}			t_pdata;

bool		ft_cmp(char *s1, char *s2);
int			ft_len(char *str);
int			ft_mlen(char **str);
int			ft_maxlen(char **str);
char		*ft_dup(char *str);
char		**ft_strsplit(char *str, char c);
int			ft_nw(char *ss, char cc);
char		*ft_sub(char *str, int start, int len);
bool		ft_strstr(char *str, char *sch);
char		*ft_read_mapfile(int fd);
char		*ft_join(char *s1, char *s2);
void		ft_mjoin(char ***str, char c, int maxlen);
bool		ft_check_ext(char *str, char *ext);
bool		ft_check_char(char *str, char c);
bool		ft_strstr_1(char *str, char *sch);
bool		ft_sch(char *str, char c);
void		ft_check_error(int ac, char *av, t_pdata *data);
void		ft_put_error(char *str);
//stucts functions
void		ft_init_struct(t_pdata *data);
void		ft_fill_struct(t_pdata *data);
char		*ft_get_data(char **str, char *sch, int lo);

//prints
void		ft_mprint(char **str);
void		ft_print_struct(t_pdata *data, char *msg);
void		ft_tprint(char **str, int _y, int _x);
// rgb functon
bool		ft_check_rgb(char *str, char *sch);
long		ft_char_2_int(char *str);
void		ft_get_rgb(char *str, t_pdata *data, char c);
/// xmp file
void		ft_check_xpm(t_pdata *data);
// check map
void		ft_check_map(t_pdata *data);
int			ft_check_element(char *str, char *sch, char *to_count);
bool		ft_check_new_line(t_pdata *data);
int			ft_line_cmp(char *str, char *sch);
void		ft_delete_line(char **str, int start);
void		ft_bypass_char(char *str, int *i, char c, int revrse);
bool		ft_valid_char(t_pmap *dmap, char to_check, char *sch);
void		ft_free(char **str);

#endif