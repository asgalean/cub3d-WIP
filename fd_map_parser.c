/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_map_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuello <mcuello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 12:49:19 by mcuello           #+#    #+#             */
/*   Updated: 2026/03/25 21:34:21 by mcuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty_line(char *line)
{
	while (*line == ' ' || *line == '\n')
		line++;
	if (*line == '\0')
		return (1);
	return (0);
}

static int	fill_map(t_fd *fd_data, t_map *map, int start)
{
	int	len;
	int	j;

	j = 0;
	while (fd_data->line[start + j])
	{
		len = ft_strlen(fd_data->line[start + j]);
		if (fd_data->line[start + j][len - 1] == '\n')
			fd_data->line[start + j][len - 1] = '\0';
		if (fd_data->line[start + j][0] == '\0')
			break ;
		if (is_empty_line(fd_data->line[start + j]))
			break ;
		map->map[j] = ft_strdup(fd_data->line[start + j]);
		if (!map->map[j])
			return (ft_error("Error: fallo en el parseo del mapa.\n"), -1);
		if ((int)ft_strlen(map->map[j]) > map->width)
			map->width = len;
		j++;
	}
	map->map[j] = NULL;
	return (j);
}

int	parse_map(t_fd *fd_data, int start)
{
	t_map	*map;
	int		fill;

	map = fd_data->map;
	map->height = fd_data->height - start;
	map->width = 0;
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		return (ft_error("Error: fallo en el parseo del mapa.\n"), -1);
	fill = fill_map(fd_data, map, start);
	map->height = fill;
	while (fd_data->line[start + fill])
	{
		if (!is_empty_line(fd_data->line[start + fill]))
		{
			ft_error("Error: contenido invalido despues del mapa.\n");
			return (-1);
		}
		fill++;
	}
	return (0);
}
