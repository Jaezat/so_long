/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 08:58:53 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/14 18:12:22 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*get_tile_img(t_map *d_map, char c)
{
	if (c == '1')
		return (d_map->v->img_wall.img);
	else if (c == '0')
		return (d_map->v->img_floor.img);
	else if (c == 'P')
		return (d_map->v->img_player.img);
	else if (c == 'C')
		return (d_map->v->img_collectible.img);
	else if (c == 'E')
		return (d_map->v->img_exit.img);
	return (d_map->v->img_floor.img);
}

static int	load_image(void *mlx, void **img, char *path)
{
	int	w;
	int	h;

	w = 32;
	h = 32;
	*img = mlx_xpm_file_to_image(mlx, path, &w, &h);
	if (!*img)
		return (1);
	return (0);
}

int	init_images(t_map *d_map)
{
	void	*mlx;

	mlx = d_map->v->mlx;
	if (load_image(mlx, &d_map->v->img_wall.img, "images/wall.xpm"))
		return (1);
	if (load_image(mlx, &d_map->v->img_floor.img, "images/floor.xpm"))
		return (1);
	if (load_image(mlx, &d_map->v->img_player.img, "images/player.xpm"))
		return (1);
	if (load_image(mlx, &d_map->v->img_collectible.img,
			"images/collectibles.xpm"))
		return (1);
	if (load_image(mlx, &d_map->v->img_exit.img, "images/exit.xpm"))
		return (1);
	return (0);
}
