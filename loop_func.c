/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgalean <asgalean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:11:52 by asgalean          #+#    #+#             */
/*   Updated: 2026/03/25 17:11:55 by asgalean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_pp.h"

static void	select_wall(t_data *data, t_ray *ray, mlx_texture_t **tex) //mergear con manu
{
	if (ray->face == 'N')
		*tex = data->tex_n;
	else if (ray->face == 'S')
		*tex = data->tex_s;
	else if (ray->face == 'E')
		*tex = data->tex_e;
	else
		*tex = data->tex_w;
}

static void	pixel_col_init(t_pixel_col *pixel_col, t_ray *ray,
			mlx_texture_t *tex)
{
	pixel_col->tex_x = (int)(ray->wall_percent * tex->width);
	pixel_col->wall_size = (int)(HEIGHT / (ray->dist * 3));
	pixel_col->real_wall_size = pixel_col->wall_size;
	if (pixel_col->wall_size > HEIGHT)
		pixel_col->wall_size = HEIGHT;
	pixel_col->top = (HEIGHT - pixel_col->real_wall_size) / 2;
	if (pixel_col->top < 0)
		pixel_col->draw_start = 0;
	else
		pixel_col->draw_start = pixel_col->top;
	if ((pixel_col->top + pixel_col->real_wall_size) > HEIGHT)
		pixel_col->draw_end = HEIGHT;
	else
		pixel_col->draw_end = pixel_col->top + pixel_col->real_wall_size;
	if (pixel_col->top < 0)
		pixel_col->tex_pos_start = (double)(-pixel_col->top)
			/ pixel_col->real_wall_size;
	else
		pixel_col->tex_pos_start = 0.0;
}

//******************************************************************************

static void	draw_column(t_pixel_col *pixel_col, mlx_texture_t *tex,
		t_data *data, int i)
{
	int	y;

	y = 0;
	while (y < pixel_col->draw_start)
		mlx_put_pixel(data->img, i, y++, 0x87CEEBFF);
	while (y < pixel_col->draw_end)
	{
		pixel_col->tex_pos = pixel_col->tex_pos_start + (double)(y
				- pixel_col->draw_start) / pixel_col->real_wall_size;
		pixel_col->tex_y = (int)(pixel_col->tex_pos * tex->height);
		pixel_col->idx = (pixel_col->tex_y * tex->width
				+ pixel_col->tex_x) * 4;
		pixel_col->color = (tex->pixels[pixel_col->idx] << 24
				| tex->pixels[pixel_col->idx + 1] << 16
				| tex->pixels[pixel_col->idx + 2] << 8
				| tex->pixels[pixel_col->idx + 3]);
		mlx_put_pixel(data->img, i, y++, pixel_col->color);
	}
	while (y < HEIGHT)
		mlx_put_pixel(data->img, i, y++, 0x654321FF);
}

void	loop_func(void *param)
{
	t_data			*data;
	mlx_texture_t	*tex;
	double			ray_angle_and_i[2];
	t_pixel_col		pixel_col;
	t_ray			ray;

	ray_angle_and_i[1] = 0;
	data = (t_data *) param;
	ray_angle_and_i[0] = fmod(data->player.angle + FOV / 2, 360);
	ft_hook(data);
	while (ray_angle_and_i[1] < WIDTH)
	{
		if (ray_angle_and_i[0] < 0)
			ray_angle_and_i[0] += 360;
		ray = cast_ray(ray_angle_and_i[0], data);
		select_wall(data, &ray, &tex);
		pixel_col_init(&pixel_col, &ray, tex);
		draw_column(&pixel_col, tex, data, ray_angle_and_i[1]);
		ray_angle_and_i[0] -= (double) FOV / WIDTH;
		ray_angle_and_i[1] += 1;
	}
}
