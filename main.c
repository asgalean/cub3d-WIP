/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuello <mcuello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:45:37 by mcuello           #+#    #+#             */
/*   Updated: 2026/03/25 16:55:04 by mcuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_error(char *str)
{
	printf("%s", str);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;
	t_fd	fd_content;

	if (argc != 2)
	{
		printf("Uso: %s <mapa.cub>\n", argv[0]);
		return (1);
	}
	if (check_extension(argv[1]) == -1)
	{
		ft_error("Error: El archivo debe tener la extension .cub\n");
		return (1);
	}
	if (read_fd(argv[1], &fd_content) == -1)
		return (1);
	if (parse_fd(argv[1], &fd_content) == -1)
		return (free_fd(&fd_content), 1);
	fd_content.map = &map;
	if (parse_map(&fd_content, fd_content.map_start) == -1)
		return (free_fd(&fd_content), free_map(map.map), 1);
	if (is_valid_map(&map) == -1)
		return (free_fd(&fd_content), free_map(map.map), 1);
	if (set_game(&fd_content, &game) == 1)
		return (free_fd(&fd_content), free_map(map.map), 1);
	if (validate_mlx(&game, &fd_content))
		return (623);
	mlx_loop_hook(game.mlx, loop_func, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_fd(&fd_content);
	free_map(map.map);
	return (0);
}
