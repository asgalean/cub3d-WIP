/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init_game.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgalean <asgalean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:08:12 by asgalean          #+#    #+#             */
/*   Updated: 2026/03/25 20:08:15 by asgalean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	texture_loading(t_game *game, t_fd *fd)
{
	game->text_n = mlx_load_png(fd->no_texture);
	if (!game->text_n)
	{
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	game->text_s = mlx_load_png(fd->so_texture);
	if (!game->text_s)
	{
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	game->text_e = mlx_load_png(fd->ea_texture);
	if (!game->text_e)
	{
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	game->text_w = mlx_load_png(fd->we_texture);
	if (!game->text_w)
	{
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	return (0);
}

int	validate_mlx(t_game *game, t_fd *fd)
{
	game->mlx = mlx_init(RES_WIDTH, RES_HEIGHT, "CUB3D", true);
	if (!game->mlx)
	{
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	game->img = mlx_new_image(game->mlx, RES_WIDTH, RES_HEIGHT);
	if (!game->img)
	{
		mlx_close_window(game->mlx);
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		perror(mlx_strerror(mlx_errno));
		return (1);
	}
	if (texture_loading(game, fd) == 1)
		return (1);
	return (0);
}

void	clean_and_close(t_game *data, t_fd *fd_content, t_map *map)
{
	if (data->text_n)
		mlx_delete_texture(data->text_n);
	if (data->text_s)
		mlx_delete_texture(data->text_s);
	if (data->text_e)
		mlx_delete_texture(data->text_e);
	if (data->text_w)
		mlx_delete_texture(data->text_w);
	if (data->img)
		mlx_delete_image(data->mlx, data->img);
	if (data->mlx)
		mlx_terminate(data->mlx);
	free_fd(fd_content);
	free_map(map->map);
}
