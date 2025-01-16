/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:38 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/16 20:05:02 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../libraries/MLX42/include/MLX42/MLX42.h"
#include "../libraries/libft/libft.h"
#include "get_next_line.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#define	WIDTH		1900
#define	HEIGHT		1000
#define	TILE_SIZE	32
#define	M_TILE_SIZE	32
#define	HITBOX		4
#define	SPEED		4
#define	ROT_SPEED	0.045
#define	FOV			60

#define	WHITE		0xFFFFFFFF
#define BLACK		0x000000FF
#define RED			0xFF0000FF
#define	GREEN		0x00FF00FF

typedef	struct		s_player
{
	mlx_image_t*	imge;
	mlx_image_t*	line;
	int				x;
	int				y;
	int				walk_dir;
	int				turn_dir;
	int				strafe_dir;
	double			rot_angle;
	double			fov;
}					t_player;

typedef	struct		s_ray
{
	double			angle;
	double			distance;
	bool			h_cross;
	bool			v_cross;
	bool			face_up;
	bool			face_down;
	bool			face_left;
	bool			face_right;
	bool			x;
}					t_ray;

typedef	struct		s_data
{
	const char*		map;
	char**			map_arr;
	int				map_height;
	mlx_t*			game;
	mlx_image_t*	wall;
	mlx_image_t*	space;
	mlx_image_t*	blank;
	mlx_image_t*	render;
	t_player*		player;
	t_ray*			ray;
}					t_data;

void	init_data(t_data *data, char *arg);
void	load_game(t_data **data);
void	get_player_position(t_data *data, int *x, int *y);
void	load_player(t_data **data);
void	load_images(t_data **data);
void	load_ray(t_data **data);

void	import_map(t_data **data, char *path);
void	draw_minimap(t_data	*data);
void	draw_tile(mlx_image_t *image, int color);
void	draw_player(mlx_image_t *image);
int		get_map_height(char **map);
