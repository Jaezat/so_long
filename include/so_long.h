/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mariacos <mariacos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 17:05:57 by mariacos          #+#    #+#             */
/*   Updated: 2025/11/15 16:46:42 by mariacos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

/* ========== LIBRARIES ========== */
# include "../libft/include/libft.h"
# include "../libft/include/get_next_line.h"
# include "../mlx_linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

/*  DEFINES  */

# define ESC 65307

/*  STRUCTURES  */

typedef struct s_chars
{
	int	e;
	int	p;
	int	c;
	int	total_c;
	int	total_e;
}	t_characters;

typedef struct s_image
{
	char	*relative_path;
	void	*img;
	int		img_width;
	int		img_height;
}	t_image;

typedef struct s_mlxvar
{
	int		x;
	int		y;
	void	*mlx;
	void	*mlx_win;
	t_image	img_wall;
	t_image	img_floor;
	t_image	img_exit;
	t_image	img_collectible;
	t_image	img_player;
}	t_mlxvar;

typedef struct s_check_wall
{
	int	not_a_wall;
	int	last_row_y;
	int	last_row_x;
}	t_check_walls;

typedef struct s_map
{
	int				x;
	int				y;
	char			**map;
	char			*line;
	char			*map_name;
	int				player_x;
	int				player_y;
	int				steps_count;
	int				tile_under_player;
	t_mlxvar		*v;
	t_characters	*collect;
}	t_map;

/*  MAP FUNCTIONS  */

// Map initialization (map_init.c)
char	*modify_map_name(char *name);
int		check_map_extension(char *filename);
int		start_engine(t_map *d_map);
int		check_map(t_map *d_map, char *map_name);

// Map parsing (map_parsing.c)
int		open_map(int *file_map, char *map_name);
int		check_height_width_map(t_map *d_map, int file_map);
int		set_2d_array(t_map *d_map, char ***map, char *map_name);

// Map validation (map_validation.c)
int		check_walls(t_map *d_map, t_check_walls *var);
int		check_collectibles_e_p_c(t_map *d_map);
int		check_num_characters(t_map *d_map);
int		check_criterias_map(t_map *d_map, char *map_name);

// Map pathfinding (map_pathfinding.c)
void	flood_fill(t_map *d_map, char **copy_map, int i, int j);
int		checking_collectibles(t_map *d_map, char *map_name);
int		find_p(char **copy_map, int *i, int *j);

/*  GRAPHICS FUNCTIONS */

// Draw map (draw_map.c)
int		load_textures(t_map *d_map);

// Image loader (image_loader.c)
void	*get_tile_img(t_map *d_map, char c);
int		init_images(t_map *d_map);

// MLX initialization (mlx_init.c)
void	set_mlx_to_null(t_map *d_map);
int		initialize_mlx(t_map *d_map);
int		close_window(t_map *d_map);

// Movement (movement.c)
void	decide_moves(t_map *d_map, char *tile_at_new_pos, int new_x, int new_y);
int		move_keycode(int keycode, int *new_x, int *new_y);
int		key_hook(int keycode, t_map *d_map);

/*  UTILS FUNCTIONS */

// Error handling (error.c)
void	return_error(char *msg);

// Cleanup (cleanup.c)
void	cleanup_all(t_map *d_map);
void	free_mlx(t_map *d_map);
void	free_images(t_map *d_map);
void	help_clean_main(t_map *d_map);

#endif
