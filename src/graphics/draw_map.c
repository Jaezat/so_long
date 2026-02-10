/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:00:30 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/14 17:47:14 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	put_tile(t_map *d_map, void *img, int x, int y)
{
	mlx_put_image_to_window(d_map->v->mlx, d_map->v->mlx_win,
		img, (x * 36) + 2, (y * 36) + 2);
}

static void	render_tile(t_map *d_map, int x, int y)
{
	void	*img;

	if (d_map->map[y][x] != 'P')
	{
		img = get_tile_img(d_map, d_map->map[y][x]);
		put_tile(d_map, img, x, y);
	}
}

static void	render_player(t_map *d_map)
{
	if (d_map->tile_under_player == 'E')
		put_tile(d_map, d_map->v->img_player.img,
			d_map->player_x, d_map->player_y);
	else
		put_tile(d_map, d_map->v->img_player.img,
			d_map->player_x, d_map->player_y);
}

int	load_textures(t_map *d_map)
{
	int	y;
	int	x;

	y = 0;
	while (y < d_map->y)
	{
		x = 0;
		while (x < d_map->x)
		{
			render_tile(d_map, x, y);
			x++;
		}
		y++;
	}
	render_player(d_map);
	return (0);
}
