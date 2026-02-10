/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:01:37 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/14 18:26:46 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	decide_moves(t_map *d_map, char *tile_at_new_pos, int new_x, int new_y)
{
	d_map->steps_count++;
	ft_printf("Steps taken: %d\n", d_map->steps_count);
	*tile_at_new_pos = d_map->map[new_y][new_x];
	if (d_map->map[new_y][new_x] == 'C')
		d_map->collect->total_c++;
	if (d_map->map[new_y][new_x] == 'E' &&
			d_map->collect->c == d_map->collect->total_c)
	{
		cleanup_all(d_map);
		exit(0);
	}
	d_map->map[d_map->player_y][d_map->player_x] = d_map->tile_under_player;
	if (*tile_at_new_pos == 'C')
		d_map->tile_under_player = '0';
	else if (*tile_at_new_pos == 'E')
		d_map->tile_under_player = 'E';
	else if (*tile_at_new_pos == '0')
		d_map->tile_under_player = '0';
	else
		d_map->tile_under_player = *tile_at_new_pos;
	d_map->player_x = new_x;
	d_map->player_y = new_y;
	d_map->map[new_y][new_x] = 'P';
}

int	move_keycode(int keycode, int *new_x, int *new_y)
{
	if (keycode == 13 || keycode == 119)
		(*new_y) -= 1;
	else if (keycode == 1 || keycode == 115)
		(*new_y) += 1;
	else if (keycode == 0 || keycode == 97)
		(*new_x) -= 1;
	else if (keycode == 2 || keycode == 100)
		(*new_x) += 1;
	else
		return (0);
	return (1);
}

int	key_hook(int keycode, t_map *d_map)
{
	char	tile_at_new_pos;
	int		new_x;
	int		new_y;

	if (keycode == 65307)
	{
		cleanup_all(d_map);
		exit(0);
	}
	tile_at_new_pos = 0;
	new_x = d_map->player_x;
	new_y = d_map->player_y;
	if (!move_keycode(keycode, &new_x, &new_y))
		return (0);
	if (d_map->map[new_y][new_x] != '1')
		decide_moves(d_map, &tile_at_new_pos, new_x, new_y);
	mlx_clear_window(d_map->v->mlx, d_map->v->mlx_win);
	load_textures(d_map);
	return (0);
}
