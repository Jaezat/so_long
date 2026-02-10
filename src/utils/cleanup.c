/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 14:31:17 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/15 16:46:22 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_images(t_map *d_map)
{
	if (!d_map || !d_map->v || !d_map->v->mlx)
		return ;
	if (d_map->v->img_wall.img)
		mlx_destroy_image(d_map->v->mlx, d_map->v->img_wall.img);
	if (d_map->v->img_floor.img)
		mlx_destroy_image(d_map->v->mlx, d_map->v->img_floor.img);
	if (d_map->v->img_player.img)
		mlx_destroy_image(d_map->v->mlx, d_map->v->img_player.img);
	if (d_map->v->img_collectible.img)
		mlx_destroy_image(d_map->v->mlx, d_map->v->img_collectible.img);
	if (d_map->v->img_exit.img)
		mlx_destroy_image(d_map->v->mlx, d_map->v->img_exit.img);
}

void	free_mlx(t_map *d_map)
{
	if (!d_map || !d_map->v)
		return ;
	if (d_map->v->mlx_win)
		mlx_destroy_window(d_map->v->mlx, d_map->v->mlx_win);
	if (d_map->v->mlx)
	{
		mlx_destroy_display(d_map->v->mlx);
		free(d_map->v->mlx);
	}
	free(d_map->v);
	d_map->v = NULL;
}

void	cleanup_all(t_map *d_map)
{
	if (!d_map)
		return ;
	if (d_map->map_name)
		free(d_map->map_name);
	if (d_map->v)
	{
		free_images(d_map);
		free_mlx(d_map);
	}
	if (d_map->map)
		free_2d_array(d_map->map);
	if (d_map->collect)
		free(d_map->collect);
	free(d_map);
}

void	help_clean_main(t_map *d_map)
{
	cleanup_all(d_map);
	exit(EXIT_FAILURE);
}
