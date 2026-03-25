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
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	game->text_s = mlx_load_png(fd->so_texture);
	if (!game->text_s)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	game->text_e = mlx_load_png(fd->ea_texture);
	if (!game->text_e)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	game->text_w = mlx_load_png(fd->we_texture);
	if (!game->text_w)
	{
		puts(mlx_strerror(mlx_errno));
		return (1);
	}
	return (0);
}

int	validate_mlx(t_game *game, t_fd *fd)
{
	if (!(game->mlx = mlx_init(RES_WIDTH, RES_HEIGHT, "CUB3D", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (!(game->img = mlx_new_image(game->mlx, RES_WIDTH, RES_HEIGHT)))
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) == -1)
	{
		mlx_close_window(game->mlx);
		puts(mlx_strerror(mlx_errno));
		return(1);
	}
	if(texture_loading(game, fd) == 1)
		return (1);
	return (0);
}

void	clean_and_close(t_game *data)
{
	mlx_close_window(data->mlx);
	//mlx_delete_image(data->mlx, data->img);
	//mlx_delete_texture(data->text_n);
	//mlx_delete_texture(data->text_s);
	//mlx_delete_texture(data->text_e);
	//mlx_delete_texture(data->text_w);
	//mlx_terminate(data->mlx);
}
