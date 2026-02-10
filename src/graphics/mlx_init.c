/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 09:03:19 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/14 18:17:53 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	close_window(t_map *d_map)
{
	cleanup_all(d_map);
	exit(0);
	return (0);
}

void	set_mlx_to_null(t_map *d_map)
{
	d_map->v->mlx = NULL;
	d_map->v->mlx_win = NULL;
	d_map->v->img_wall.img = NULL;
	d_map->v->img_floor.img = NULL;
	d_map->v->img_player.img = NULL;
	d_map->v->img_collectible.img = NULL;
	d_map->v->img_exit.img = NULL;
}

int	initialize_mlx(t_map *d_map)
{
	d_map->collect->total_c = 0;
	d_map->v = malloc(sizeof(t_mlxvar));
	if (!d_map->v)
		return (1);
	set_mlx_to_null(d_map);
	d_map->v->mlx = mlx_init();
	if (!d_map->v->mlx)
		return (1);
	d_map->v->mlx_win = mlx_new_window(d_map->v->mlx,
			d_map->x * 36, d_map->y * 36, "Electric Game");
	if (!d_map->v->mlx_win)
		return (1);
	if (init_images(d_map) == 1)
	{
		return_error("Failed to load images");
		return (1);
	}
	if (load_textures(d_map) == 1)
		return (1);
	mlx_key_hook(d_map->v->mlx_win, key_hook, d_map);
	mlx_hook(d_map->v->mlx_win, 17, 0, close_window, d_map);
	mlx_loop(d_map->v->mlx);
	return (0);
}
