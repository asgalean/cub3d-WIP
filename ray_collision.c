/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_collision.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgalean <asgalean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:12:19 by asgalean          #+#    #+#             */
/*   Updated: 2026/03/25 17:12:21 by asgalean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_pp.h"

static double	pitagoras(double collision_x, double collision_y, t_data *data)
{
	double	hypotenuse;

	hypotenuse = sqrt(
			(collision_x - data->player.X) * (collision_x - data->player.X)
			+ (collision_y - data->player.Y) * (collision_y - data->player.Y));
	return (hypotenuse);
}

//******************************************************************************
//******************************************************************************

static void	h_init(double *const_increment_x,
					double *const_increment_y, double angle)
{
	if (angle >= PIH && angle <= PI3H)
		*const_increment_x = -1;
	else
		*const_increment_x = 1;
	if (angle >= 0 && angle <= PI)
		*const_increment_y = fabs(tan(angle)) * -1;
	else
		*const_increment_y = fabs(tan(angle)) * 1;
}

//horizontal collision, ray goes in X axis
double	h_collision(double angle, t_data *data, t_ray *h_ray)
{
	double	const_increment_x;
	double	const_increment_y;
	int		matrix_x;
	int		matrix_y;
	int		i;

	i = -1;
	h_init(&const_increment_x, &const_increment_y, angle);
	h_ray->collision_x = ((int)(data->player.X)
			+ (angle < PIH || angle > PI3H));
	h_ray->collision_y = data->player.Y
		- (h_ray->collision_x - data->player.X) * tan(angle);
	while (++i < MAX_RAY_ITERATION)
	{
		matrix_x = (int)(h_ray->collision_x);
		matrix_y = (int)(h_ray->collision_y);
		if (matrix_x >= 0 && matrix_x < MAP_WIDTH
			&& matrix_y >= 0 && matrix_y < MAP_HEIGHT
			&& (data->map[matrix_y][matrix_x - (const_increment_x < 0)] == '1'
			|| data->map[matrix_y][matrix_x - (const_increment_x < 0)] == ' '))
			return (pitagoras(h_ray->collision_x, h_ray->collision_y, data));
		h_ray->collision_x += const_increment_x;
		h_ray->collision_y += const_increment_y;
	}
	return (pitagoras(h_ray->collision_x, h_ray->collision_y, data));
}

//******************************************************************************
//******************************************************************************

static void	v_init(double *const_increment_x,
					double *const_increment_y, double angle)
{
	if (angle >= 0 && angle <= PI)
		*const_increment_y = -1;
	else
		*const_increment_y = 1;
	if (angle >= PIH && angle <= PI3H)
		*const_increment_x = -1 / fabs(tan(angle));
	else
		*const_increment_x = 1 / fabs(tan(angle));
}

//vertical collision, ray goes in Y axis
double	v_collision(double angle, t_data *data, t_ray *v_ray)
{
	double	const_increment_x;
	double	const_increment_y;
	int		matrix_x;
	int		matrix_y;
	int		i;

	i = -1;
	v_init(&const_increment_x, &const_increment_y, angle);
	v_ray->collision_y = ((int)(data->player.Y)
			+ (angle > PI && angle < (2 * PI)));
	v_ray->collision_x = data->player.X
		- (v_ray->collision_y - data->player.Y) / tan(angle);
	while (++i < MAX_RAY_ITERATION)
	{
		matrix_x = (int)(v_ray->collision_x);
		matrix_y = (int)(v_ray->collision_y);
		if (matrix_x >= 0 && matrix_x < MAP_WIDTH
			&& matrix_y >= 0 && matrix_y < MAP_HEIGHT
			&& (data->map[matrix_y - (const_increment_y < 0)][matrix_x] == '1'
			|| data->map[matrix_y - (const_increment_y < 0)][matrix_x] == ' '))
			return (pitagoras(v_ray->collision_x, v_ray->collision_y, data));
		v_ray->collision_x += const_increment_x;
		v_ray->collision_y += const_increment_y;
	}
	return (pitagoras(v_ray->collision_x, v_ray->collision_y, data));
}
