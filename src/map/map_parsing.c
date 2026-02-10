/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:43:27 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/15 15:00:32 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	open_map(int *file_map, char *map_name)
{
	*file_map = open(map_name, O_RDONLY);
	if (*file_map < 0)
	{
		return_error("Map file does not exist or cannot be opened.");
		return (1);
	}
	return (0);
}

static int	check_line_length(t_map *d_map, int *diff_length)
{
	int	length_line;

	length_line = (ft_strlen(d_map->line) - 1);
	if (d_map->line[length_line] != '\n')
		length_line++;
	if (length_line != d_map->x)
		(*diff_length)++;
	return (0);
}

static int	handle_error(char *message)
{
	return_error(message);
	return (1);
}

int	check_height_width_map(t_map *d_map, int file_map)
{
	int	diff_length;

	diff_length = 0;
	d_map->y = 1;
	d_map->line = get_next_line(file_map);
	if (d_map->line == NULL)
		return (handle_error("The file is empty."));
	d_map->x = ft_strlen(d_map->line);
	if (d_map->line[d_map->x - 1] == '\n')
		d_map->x--;
	free(d_map->line);
	d_map->line = get_next_line(file_map);
	while (d_map->line != NULL)
	{
		d_map->y++;
		check_line_length(d_map, &diff_length);
		free(d_map->line);
		d_map->line = get_next_line(file_map);
	}
	free(d_map->line);
	if (diff_length != 0)
		return (handle_error("The map is not rectangular."));
	return (0);
}

int	set_2d_array(t_map *d_map, char ***map, char *map_name)
{
	int	i;
	int	file_map;
	int	len;

	*map = malloc(sizeof(char *) * (d_map->y + 1));
	if (!(*map))
		return (1);
	if (open_map(&file_map, map_name) == 1)
	{
		free(*map);
		*map = NULL;
		return (1);
	}
	i = -1;
	while (++i < d_map->y)
	{
		(*map)[i] = get_next_line(file_map);
		len = ft_strlen((*map)[i]);
		if (len > 0 && (*map)[i][len - 1] == '\n')
			(*map)[i][len - 1] = '\0';
	}
	(*map)[i] = NULL;
	if (file_map >= 0)
		close(file_map);
	return (0);
}
