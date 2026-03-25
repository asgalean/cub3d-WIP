/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuello <mcuello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:02:28 by mcuello           #+#    #+#             */
/*   Updated: 2026/03/25 16:02:01 by mcuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == ' ' || map[y][x] == '\0')
		return (-1);
	if (map[y][x] == 'X' || map[y][x] == '1')
		return (0);
	map[y][x] = 'X';
	if (flood_fill(map, x + 1, y) == -1)
		return (-1);
	if (flood_fill(map, x - 1, y) == -1)
		return (-1);
	if (flood_fill(map, x, y + 1) == -1)
		return (-1);
	if (flood_fill(map, x, y - 1) == -1)
		return (-1);
	return (0);
}

char	**map_copy(t_map *map)
{
	char	**map_cpy;
	int		i;

	map_cpy = malloc(sizeof(char *) * (map->height + 1));
	if (!map_cpy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		map_cpy[i] = ft_strdup(map->map[i]);
		if (!map_cpy[i])
			return (NULL);
		i++;
	}
	map_cpy[i] = NULL;
	return (map_cpy);
}

void	free_fd(t_fd *fd_data)
{
	if (fd_data->line)
		free_map(fd_data->line);
	if (fd_data->no_texture)
		free(fd_data->no_texture);
	if (fd_data->so_texture)
		free(fd_data->so_texture);
	if (fd_data->we_texture)
		free(fd_data->we_texture);
	if (fd_data->ea_texture)
		free(fd_data->ea_texture);
	if (fd_data->floor_color)
		free(fd_data->floor_color);
	if (fd_data->ceiling_color)
		free(fd_data->ceiling_color);
	return ;
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
