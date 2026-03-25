/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgalean <asgalean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:12:01 by asgalean          #+#    #+#             */
/*   Updated: 2026/03/25 17:12:02 by asgalean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_pp.h"

static t_ray	ray_choosing(t_ray *h_ray, t_ray *v_ray,
				double angle, t_data *data)
{
	double	rad_angle;
	t_ray	final_ray;

	rad_angle = angle * ANGLE_TO_RADIAN;
	if (h_ray->dist < v_ray->dist)
	{
		final_ray.dist = h_ray->dist * cos((angle - data->player.angle)
				* ANGLE_TO_RADIAN);
		final_ray.wall_percent = h_ray->collision_y - (int)h_ray->collision_y;
		if (rad_angle > PIH && rad_angle < PI3H)
			final_ray.face = 'W';
		else
			final_ray.face = 'E';
	}
	else
	{
		final_ray.dist = v_ray->dist * cos((angle - data->player.angle)
				* ANGLE_TO_RADIAN);
		final_ray.wall_percent = v_ray->collision_x - (int)v_ray->collision_x;
		if (rad_angle > 0 && rad_angle < PI)
			final_ray.face = 'N';
		else
			final_ray.face = 'S';
	}
	return (final_ray);
}

//******************************************************************************
//******************************************************************************

t_ray	cast_ray(double angle, t_data *data)
{
	double	rad_angle;
	t_ray	h_ray;
	t_ray	v_ray;
	t_ray	final_ray;

	rad_angle = angle * ANGLE_TO_RADIAN;
	h_ray.dist = h_collision(rad_angle, data, &h_ray);
	v_ray.dist = v_collision(rad_angle, data, &v_ray);
	final_ray = ray_choosing(&h_ray, &v_ray, angle, data);
	if (final_ray.face == 'S' || final_ray.face == 'W')
		final_ray.wall_percent = 1.0 - final_ray.wall_percent;
	return (final_ray);
}
