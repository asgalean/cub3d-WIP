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

#include "cub3d.h"

static void	h_movement(t_game *data, double rad)
{
	char	**map;

	map = data->map->map;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
	{
		if (map[(int)(data->player.y - cos(rad)
				* data->player.speed)][(int)(data->player.x)] != '1')
			data->player.y -= cos(rad) * data->player.speed;
		if (map[(int)(data->player.y)][(int)(data->player.x - sin(rad)
			* data->player.speed)] != '1')
			data->player.x -= sin(rad) * data->player.speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
	{
		if (map[(int)(data->player.y + cos(rad)
				* data->player.speed)][(int)(data->player.x)] != '1')
			data->player.y += cos(rad) * data->player.speed;
		if (map[(int)(data->player.y)][(int)(data->player.x + sin(rad)
			* data->player.speed)] != '1')
			data->player.x += sin(rad) * data->player.speed;
	}
}

static void	v_movement(t_game *data, double rad)
{
	char	**map;

	map = data->map->map;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
	{
		if (map[(int)(data->player.y - sin(rad)
				* data->player.speed)][(int)(data->player.x)] != '1')
			data->player.y -= sin(rad) * data->player.speed;
		if (map[(int)(data->player.y)][(int)(data->player.x + cos(rad)
			* data->player.speed)] != '1')
			data->player.x += cos(rad) * data->player.speed;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
	{
		if (map[(int)(data->player.y + sin(rad)
				* data->player.speed)][(int)(data->player.x)] != '1')
			data->player.y += sin(rad) * data->player.speed;
		if (map[(int)(data->player.y)][(int)(data->player.x - cos(rad)
			* data->player.speed)] != '1')
			data->player.x -= cos(rad) * data->player.speed;
	}
}

//******************************************************************************

void	ft_hook(t_game *data)
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
