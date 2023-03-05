# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
#include <math.h>
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int	    width;
    int     height;
}				t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int get_color(t_data *tswira, int y, int x)
{
    int *color;

    color = (int *) (tswira->addr + (y * tswira->line_length + x * (tswira->bits_per_pixel / 8)));
    return (*color);
}

int main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
    t_data tswira;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
	img.img = mlx_new_image(mlx, 500, 500);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    tswira.img = mlx_xpm_file_to_image(mlx, "zelij.xpm", &tswira.width, &tswira.height);
    tswira.addr = mlx_get_data_addr(tswira.img, &tswira.bits_per_pixel, &tswira.line_length,
								&tswira.endian);
    double xx = 0;
    double yy = 0;
    for (int y = 0; y < 500; y++)
    {
        xx = 0;
        for (int x = 0; x < 500; x++)
        {
            my_mlx_pixel_put(&img, x, y, get_color(&tswira, (int)yy, (int)xx));
            xx += (double) tswira.width / 500;
        }
        yy += (double) tswira.height / 500;
    }
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);

}
