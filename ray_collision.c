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

#include "cub3d.h"

static double	pitagoras(double collision_x, double collision_y, t_game *data)
{
	double	hypotenuse;

	hypotenuse = sqrt(
			(collision_x - data->player.x) * (collision_x - data->player.x)
			+ (collision_y - data->player.y) * (collision_y - data->player.y));
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
double	h_collision(double angle, t_game *data, t_ray *h_ray)
{
	double	const_increment_x;
	double	const_increment_y;
	int		matr_x;
	int		matr_y;
	int		i;

	i = -1;
	h_init(&const_increment_x, &const_increment_y, angle);
	h_ray->collision_x = ((int)(data->player.x)
			+ (angle < PIH || angle > PI3H));
	h_ray->collision_y = data->player.y
		- (h_ray->collision_x - data->player.x) * tan(angle);
	while (++i < MAX_RAY_ITERATION)
	{
		matr_x = (int)(h_ray->collision_x);
		matr_y = (int)(h_ray->collision_y);
		if (matr_x >= 0 && matr_x < data->map->width
			&& matr_y >= 0 && matr_y < data->map->height
			&& (data->map->map[matr_y][matr_x - (const_increment_x < 0)] == '1'
			|| data->map->map[matr_y][matr_x - (const_increment_x < 0)] == ' '))
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
double	v_collision(double angle, t_game *data, t_ray *v_ray)
{
	double	const_increment_x;
	double	const_increment_y;
	int		matr_x;
	int		matr_y;
	int		i;

	i = -1;
	v_init(&const_increment_x, &const_increment_y, angle);
	v_ray->collision_y = ((int)(data->player.y)
			+ (angle > PI && angle < (2 * PI)));
	v_ray->collision_x = data->player.x
		- (v_ray->collision_y - data->player.y) / tan(angle);
	while (++i < MAX_RAY_ITERATION)
	{
		matr_x = (int)(v_ray->collision_x);
		matr_y = (int)(v_ray->collision_y);
		if (matr_x >= 0 && matr_x < data->map->width
			&& matr_y >= 0 && matr_y < data->map->height
			&& (data->map->map[matr_y - (const_increment_y < 0)][matr_x] == '1'
			|| data->map->map[matr_y - (const_increment_y < 0)][matr_x] == ' '))
			return (pitagoras(v_ray->collision_x, v_ray->collision_y, data));
		v_ray->collision_x += const_increment_x;
		v_ray->collision_y += const_increment_y;
	}
	return (pitagoras(v_ray->collision_x, v_ray->collision_y, data));
}
