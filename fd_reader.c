/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_reader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuello <mcuello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:47:57 by mcuello           #+#    #+#             */
/*   Updated: 2026/03/25 15:50:12 by mcuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int	read_fd(char *filename, t_fd *fd_data)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_error("Error: Fallo al leer el descriptor de archivo.\n");
		return (-1);
	}
	fd_data->height = count_lines(fd);
	if (fd_data->height == 0)
	{
		ft_error("Error: Fallo al leer el descriptor de archivo.\n");
		return (-1);
	}
	fd_data->line = malloc(sizeof(char *) * (fd_data->height + 1));
	if (!fd_data->line)
	{
		ft_error("Error: Fallo al leer el descriptor de archivo.\n");
		return (-1);
	}
	return (0);
}
