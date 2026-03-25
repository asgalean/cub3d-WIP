/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_parser_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuello <mcuello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:21:31 by mcuello           #+#    #+#             */
/*   Updated: 2026/03/25 16:13:23 by mcuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_rgb(char *line, t_fd *fd_data)
{
	char	**arr;
	int		i;

	arr = ft_split(line, ' ');
	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		i++;
	if (i != 2)
		return ;
	if (arr[0][0] == 'F' && ft_strlen(arr[0]) == 1 && !fd_data->floor_color)
	{
		fd_data->floor_color = ft_strdup(arr[1]);
		fd_data->elements++;
	}
	else if (arr[0][0] == 'C' && ft_strlen(arr[0]) == 1
		&& !fd_data->ceiling_color)
	{
		fd_data->ceiling_color = ft_strdup(arr[1]);
		fd_data->elements++;
	}
	free_map(arr);
	free(line);
	return ;
}

static void	assign_we(char **arr, t_fd *fd_data)
{
	if ((arr[0][0] == 'W' && arr[0][1] == 'E' && ft_strlen(arr[0]) == 2)
		|| (arr[0][0] == 'W' && ft_strlen(arr[0]) == 1))
	{
		if (!fd_data->we_texture)
			fd_data->we_texture = ft_strdup(arr[1]);
		fd_data->elements++;
	}
	else if ((arr[0][0] == 'E' && arr[0][1] == 'A' && ft_strlen(arr[0]) == 2)
		|| (arr[0][0] == 'E' && ft_strlen(arr[0]) == 1))
	{
		if (!fd_data->ea_texture)
			fd_data->ea_texture = ft_strdup(arr[1]);
		fd_data->elements++;
	}
}

static void	assign_path(char **arr, t_fd *fd_data)
{
	if ((arr[0][0] == 'N' && arr[0][1] == 'O' && ft_strlen(arr[0]) == 2)
		|| (arr[0][0] == 'N' && ft_strlen(arr[0]) == 1))
	{
		if (!fd_data->no_texture)
			fd_data->no_texture = ft_strdup(arr[1]);
		fd_data->elements++;
	}
	else if ((arr[0][0] == 'S' && arr[0][1] == 'O' && ft_strlen(arr[0]) == 2)
		|| (arr[0][0] == 'S' && ft_strlen(arr[0]) == 1))
	{
		if (!fd_data->so_texture)
			fd_data->so_texture = ft_strdup(arr[1]);
		fd_data->elements++;
	}
	else
		assign_we(arr, fd_data);
	return ;
}

void	get_path(char *line, t_fd *fd_data)
{
	char	**arr;
	int		i;

	arr = ft_split(line, ' ');
	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		i++;
	if (i != 2)
		return ;
	assign_path(arr, fd_data);
	free_map(arr);
	free(line);
}
