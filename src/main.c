/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 14:56:54 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/15 16:49:05 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	t_map	*d_map;

	if (argc != 2)
	{
		return_error("Number of arguments not valid.");
		return (1);
	}
	if (check_map_extension(argv[1]) == 1)
	{
		return_error("Map name invalid.");
		return (1);
	}
	d_map = malloc(sizeof(t_map));
	if (!d_map)
		return (1);
	ft_memset(d_map, 0, sizeof(t_map));
	d_map->map_name = modify_map_name(argv[1]);
	if (d_map->map_name == NULL)
		help_clean_main(d_map);
	if (start_engine(d_map) == 1)
		help_clean_main(d_map);
	cleanup_all(d_map);
	return (0);
}
