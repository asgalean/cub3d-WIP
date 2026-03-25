/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension_rules.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcuello <mcuello@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 15:05:27 by mcuello           #+#    #+#             */
/*   Updated: 2026/03/25 15:05:31 by mcuello          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_extension(char *str)
{
	char	*extension;
	size_t	i;
	size_t	j;

	extension = ft_strdup(".cub");
	if (str[0] == '\0')
		return (-1);
	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i] && str[i + j] && (str[i + j] == extension[j]))
			j++;
		if (j == 4 && str[i + j] == '\0')
		{
			free(extension);
			if (j == ft_strlen(str))
				return (-1);
			return (0);
		}
		i++;
	}
	return (free(extension), -1);
}
