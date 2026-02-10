/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:42:22 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/15 16:41:27 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_map(t_map *d_map, char *map_name)
{
	int	file_map;

	d_map->collect = malloc(sizeof(t_characters));
	if (!d_map->collect)
		return (1);
	if (open_map(&file_map, map_name) == 1)
		return (1);
	if (check_height_width_map(d_map, file_map) == 1)
	{
		close(file_map);
		return (1);
	}
	close(file_map);
	if (check_criterias_map(d_map, map_name) == 1)
	{
		return_error("The criteria of the map didn't match.");
		return (1);
	}
	return (0);
}

int	check_map_extension(char *filename)
{
	int	len;

	if (!filename)
		return (1);
	if (ft_strcmp(filename, "maps/.ber") == 0)
		return (1);
	len = ft_strlen(filename);
	if (len < 5)
		return (1);
	if (ft_strncmp(filename + len - 4, ".ber", 4) != 0)
		return (1);
	return (0);
}

char	*modify_map_name(char *name)
{
	char	*str;

	if (ft_strnstr(name, "maps/", 5) == name)
	{
		str = ft_strdup(name);
		if (!str)
			return (NULL);
		return (str);
	}
	str = ft_strjoin("maps/", name);
	if (!str)
		return (NULL);
	return (str);
}

int	start_engine(t_map *d_map)
{
	if (check_map(d_map, d_map->map_name) == 1)
		return (1);
	if (initialize_mlx(d_map) == 1)
		return (1);
	return (0);
}
