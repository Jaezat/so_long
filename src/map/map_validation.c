/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:45:29 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/14 17:29:24 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_walls(t_map *d_map, t_check_walls *var)
{
	int	i;
	int	j;

	i = -1;
	var->not_a_wall = 0;
	var->last_row_x = d_map->x - 1;
	var->last_row_y = d_map->y - 1;
	while (d_map->map[++i])
	{
		j = -1;
		if (i == 0 || i == var->last_row_y)
		{
			while (d_map->map[i][++j])
			{
				if (d_map->map[i][j] != 49 && d_map->map[i][j] != 10)
					var->not_a_wall++;
			}
		}
		else if ((i != 0) && (d_map->map[i][0] != 49 || d_map->map[i]
			[var->last_row_x] != 49))
			var->not_a_wall++;
	}
	if (var->not_a_wall != 0)
		return (1);
	return (0);
}

int	check_collectibles_e_p_c(t_map *d_map)
{
	if (d_map->collect->e != 1 || d_map->collect->p != 1)
		return (1);
	else if (d_map->collect->c < 1)
		return (1);
	return (0);
}

static int	check_other_letter(char c)
{
	if (c != '1' && c != '0' && c != '\n')
		return (1);
	return (0);
}

int	check_num_characters(t_map *d_map)
{
	int	i;
	int	j;

	d_map->collect->c = 0;
	d_map->collect->e = 0;
	d_map->collect->p = 0;
	i = -1;
	while (d_map->map[++i])
	{
		j = -1;
		while (d_map->map[i][++j])
		{
			if (d_map->map[i][j] == 'E')
				d_map->collect->e++;
			else if (d_map->map[i][j] == 'P')
				d_map->collect->p++;
			else if (d_map->map[i][j] == 'C')
				d_map->collect->c++;
			else if (check_other_letter(d_map->map[i][j]) == 1)
				return (1);
		}
	}
	if (check_collectibles_e_p_c(d_map) == 1)
		return (1);
	return (0);
}

int	check_criterias_map(t_map *d_map, char *map_name)
{
	t_check_walls	var;

	if (set_2d_array(d_map, &(d_map->map), map_name) == 1)
		return (1);
	if (check_walls(d_map, &var) == 1)
		return (1);
	if (check_num_characters(d_map) == 1)
		return (1);
	if (checking_collectibles(d_map, map_name) == 1)
		return (1);
	return (0);
}
