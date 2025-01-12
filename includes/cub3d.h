/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:38 by adbouras          #+#    #+#             */
/*   Updated: 2025/01/12 12:40:27 by adbouras         ###   ########.fr       */
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

#define	WIDTH		1280
#define	HEIGHT		800
#define	TILE_SIZE	32
#define	M_TILE_SIZE	16
#define	HITBOX		4
#define	SPEED		2
#define	ROT_SPEED	3 * (M_PI / 180)
#define	FOV			60 * (M_PI / 180)

#define	WHITE		0xFFFFFFFF
#define BLACK		0x000000FF
#define RED			0xFF0000FF
#define	GREEN		0x00FF00FF

typedef	struct		s_player
{
	mlx_image_t*	img;
	mlx_image_t*	line;
	int				x;
	int				y;
	int				walk_dir;
	int				turn_dir;
	int				strafe_dir;
	double			rot_angle;
}					t_player;

typedef	struct		s_ray
{
	double			angle;
	double			distance;
	bool			x;
}					t_ray;

typedef	struct		s_data
{
	const char*		map;
	char**			map_arr;
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
void	load_player(t_data **data);
void	load_images(t_data **data);

void	import_map(t_data **data, char *path);
void	draw_minimap(t_data	*data);
void	draw_tile(mlx_image_t *image, int color);
void	draw_player(mlx_image_t *image);

void	ft_key_hook(void *param);
void	update_player_pos(t_data** data);
void	if_collition(t_data **data, double x, double y);

void	raycasting(t_data *data);
void	draw_vision(void *data);