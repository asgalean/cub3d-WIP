/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgalean <asgalean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 11:30:11 by asgalean          #+#    #+#             */
/*   Updated: 2026/03/25 11:30:18 by asgalean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_pp.h"

static void	h_movement(t_data *data, double rad)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (data->map[(int)(data->player.Y - cos(rad)
				* data->player.speed)][(int)(data->player.X)] != '1')
			data->player.Y -= cos(rad) * data->player.speed;
		if (data->map[(int)(data->player.Y)][(int)(data->player.X - sin(rad)
			* data->player.speed)] != '1')
			data->player.X -= sin(rad) * data->player.speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (data->map[(int)(data->player.Y + cos(rad)
				* data->player.speed)][(int)(data->player.X)] != '1')
			data->player.Y += cos(rad) * data->player.speed;
		if (data->map[(int)(data->player.Y)][(int)(data->player.X + sin(rad)
			* data->player.speed)] != '1')
			data->player.X += sin(rad) * data->player.speed;
	}
}

static void	v_movement(t_data *data, double rad)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (data->map[(int)(data->player.Y - sin(rad)
				* data->player.speed)][(int)(data->player.X)] != '1')
			data->player.Y -= sin(rad) * data->player.speed;
		if (data->map[(int)(data->player.Y)][(int)(data->player.X + cos(rad)
			* data->player.speed)] != '1')
			data->player.X += cos(rad) * data->player.speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (data->map[(int)(data->player.Y + sin(rad)
				* data->player.speed)][(int)(data->player.X)] != '1')
			data->player.Y += sin(rad) * data->player.speed;
		if (data->map[(int)(data->player.Y)][(int)(data->player.X - cos(rad)
			* data->player.speed)] != '1')
			data->player.X -= cos(rad) * data->player.speed;
	}
}

//******************************************************************************

void	ft_hook(t_data *data)
{
	double	rad;

	rad = data->player.angle * ANGLE_TO_RADIAN;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE)
		|| mlx_is_key_down(data->mlx, MLX_KEY_Q))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player.angle += 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player.angle -= 1;
	v_movement(data, rad);
	h_movement(data, rad);
}
