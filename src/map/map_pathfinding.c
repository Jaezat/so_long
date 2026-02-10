/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_pathfinding.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:47:26 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/14 17:01:11 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	clean_and_fail(char **copy_map)
{
	free_2d_array(copy_map);
	return (1);
}

int	checking_collectibles(t_map *d_map, char *map_name)
{
	char	**copy_map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	d_map->collect->total_c = 0;
	d_map->collect->total_e = 0;
	if (set_2d_array(d_map, &copy_map, map_name) == 1)
		return (clean_and_fail(copy_map));
	if (find_p(copy_map, &i, &j) == 1)
		return (clean_and_fail(copy_map));
	d_map->player_x = j;
	d_map->player_y = i;
	flood_fill(d_map, copy_map, i, j);
	if (d_map->collect->total_c != d_map->collect->c)
		return (clean_and_fail(copy_map));
	else if (d_map->collect->total_e != 1)
		return (clean_and_fail(copy_map));
	free_2d_array(copy_map);
	return (0);
}

void	flood_fill(t_map *d_map, char **copy_map, int i, int j)
{
	char	current;

	if (copy_map[i][j] == '1' || copy_map[i][j] == 'V')
		return ;
	else
	{
		current = copy_map[i][j];
		if (current == 'C')
			d_map->collect->total_c++;
		else if (current == 'E')
			d_map->collect->total_e++;
		copy_map[i][j] = 'V';
		flood_fill(d_map, copy_map, i + 1, j);
		flood_fill(d_map, copy_map, i - 1, j);
		flood_fill(d_map, copy_map, i, j + 1);
		flood_fill(d_map, copy_map, i, j - 1);
	}
}

int	find_p(char **copy_map, int *i, int *j)
{
	while (copy_map[*i])
	{
		*j = 0;
		while (copy_map[*i][*j])
		{
			if (copy_map[*i][*j] == 'P')
				return (0);
			(*j)++;
		}
		(*i)++;
	}
	return (1);
}
