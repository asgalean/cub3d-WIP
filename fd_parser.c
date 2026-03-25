/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuello <mcuello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:11:15 by mcuello           #+#    #+#             */
/*   Updated: 2026/03/25 16:12:49 by mcuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_path(t_fd *fd_data)
{
	if (!fd_data->no_texture || !fd_data->ea_texture || !fd_data->we_texture
		|| !fd_data->so_texture || !fd_data->ceiling_color
		|| !fd_data->floor_color)
		return (-1);
	return (0);
}

static void	init_elements(t_fd *fd_data)
{
	fd_data->no_texture = NULL;
	fd_data->so_texture = NULL;
	fd_data->we_texture = NULL;
	fd_data->ea_texture = NULL;
	fd_data->floor_color = NULL;
	fd_data->ceiling_color = NULL;
	fd_data->elements = 0;
}

static int	process_line(char *tmp, t_fd *fd_data)
{
	if (tmp[0] == 'N' || tmp[0] == 'S' || tmp[0] == 'W' || tmp[0] == 'E')
		get_path(tmp, fd_data);
	else if (tmp[0] == 'F' || tmp[0] == 'C')
		get_rgb(tmp, fd_data);
	else
	{
		if (tmp[0] != 0)
		{
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

static int	get_elements(t_fd *fd_data)
{
	int		i;
	char	*tmp;
	int		ret;

	i = 0;
	init_elements(fd_data);
	while (fd_data->line[i])
	{
		tmp = ft_strtrim(fd_data->line[i], " \n");
		if (!tmp)
			return (ft_error("Error: fallo en la lectura del mapa.\n"), -1);
		ret = process_line(tmp, fd_data);
		if (ret == 1)
			break ;
		i++;
	}
	if (!fd_data->line[i] || fd_data->elements != 6)
		return (ft_error("Error: invalid structure <mapa.cub>\n"), -1);
	fd_data->map_start = i;
	return (0);
}

int	parse_fd(char *filename, t_fd *fd_data)
{
	int	i;
	int	fd;

	fd = open(filename, O_RDONLY);
	i = 0;
	while (i < fd_data->height)
	{
		fd_data->line[i] = get_next_line(fd);
		if (!fd_data->line[i])
			return (ft_error("Error: fallo en el parseo del fd.\n"), -1);
		i++;
	}
	fd_data->line[i] = NULL;
	close(fd);
	if (get_elements(fd_data) == -1)
		return (-1);
	if (is_valid_path(fd_data) == -1)
		return (ft_error("Error: invalid path.\n"), -1);
	return (0);
}
