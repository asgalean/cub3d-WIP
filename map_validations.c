/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuello <mcuello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 15:35:07 by mcuello           #+#    #+#             */
/*   Updated: 2026/03/25 16:01:46 by mcuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_position(t_map *map, int i, int j)
{
	map->player++;
	map->pos_x = j;
	map->pos_y = i;
	return ;
}

static int	check_player(t_map *map)
{
	if (map->player != 1)
		return (-1);
	return (0);
}

static int	check_chars(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	map->player = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0'
					&& map->map[i][j] != 'N' && map->map[i][j] != 'S'
					&& map->map[i][j] != 'W' && map->map[i][j] != 'E'
					&& map->map[i][j] != ' ')
				return (-1);
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
					|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
				set_position(map, i, j);
			j++;
		}
		i++;
	}
	return (0);
}

static int	normalize(t_map *map)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	while (map->map[i])
	{
		len = ft_strlen(map->map[i]);
		if (len < map->width)
		{
			tmp = ft_calloc(map->width + 1, sizeof(char));
			if (!tmp)
				return (-1);
			ft_memcpy(tmp, map->map[i], len);
			ft_memset(tmp + len, ' ', map->width - len);
			tmp[map->width] = '\0';
			free(map->map[i]);
			map->map[i] = tmp;
		}
		i++;
	}
	return (0);
}

int	is_valid_map(t_map *map)
{
	char	**cp_map;

	if (normalize(map) == -1)
		return (ft_error("Error: fallo en la normalizacion del mapa.\n"), -1);
	if (check_chars(map) == -1)
		return (ft_error("Error: caracteres incorrectos en el mapa.\n"), -1);
	if (check_player(map) == -1)
		return (ft_error("Error: debe haber un jugador en el mapa.\n"), -1);
	cp_map = map_copy(map);
	if (!cp_map)
		return (ft_error("Error: fallo en map_copy\n"), -1);
	if (flood_fill(cp_map, map->pos_x, map->pos_y) == -1)
	{
		free_map(cp_map);
		ft_error("Error: el mapa esta abierto.\n");
		return (-1);
	}
	free_map(cp_map);
	return (0);
}
