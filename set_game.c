/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asgalean <asgalean@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:51:59 by mcuello           #+#    #+#             */
/*   Updated: 2026/03/26 16:48:46 by asgalean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_btoi(const char *str)
{
	long	atoi;
	int		sign;

	atoi = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		atoi *= 10;
		atoi += *str - 48;
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (atoi * sign);
}

static int	rgb_to_pixel(char *rgb, uint32_t *color)
{
	char	**arr;
	int		r;
	int		g;
	int		b;
	int		i;

	arr = ft_split(rgb, ',');
	if (!arr)
		return (-1);
	i = 0;
	while (arr[i])
		i++;
	if (i != 3)
		return (free_map(arr), -1);
	r = ft_btoi(arr[0]);
	g = ft_btoi(arr[1]);
	b = ft_btoi(arr[2]);
	free_map(arr);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	*color = (r << 24 | g << 16 | b << 8 | 0xFF);
	return (0);
}

static double	direction_selector(t_map *map)
{
	if (map->map[map->pos_y][map->pos_x] == 'N')
		return (90.05);
	if (map->map[map->pos_y][map->pos_x] == 'S')
		return (270.05);
	if (map->map[map->pos_y][map->pos_x] == 'E')
		return (0.05);
	if (map->map[map->pos_y][map->pos_x] == 'W')
		return (180.05);
	return (90.05);
}

int	set_game(t_fd *fd, t_game *game)
{
	game->player.x = fd->map->pos_x + 0.5;
	game->player.y = fd->map->pos_y + 0.5;
	game->player.angle = direction_selector(fd->map);
	game->player.speed = 0.1;
	game->map = fd->map;
	if (rgb_to_pixel(fd->ceiling_color, &game->ceiling) == -1)
		return (ft_error("Error en el color rgb"), 1);
	if (rgb_to_pixel(fd->floor_color, &game->floor) == -1)
		return (ft_error("Error en el color rgb"), 1);
	return (0);
}
