/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:38 by adbouras          #+#    #+#             */
/*   Updated: 2024/12/25 18:45:38 by adbouras         ###   ########.fr       */
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
#define	HEIGHT		720
#define	TILE_SIZE	32

#define	WHITE		0xFFFFFFFF
#define BLACK		0x000000FF
#define RED			0xFF0000FF
#define	GREEN		0x00FF00FF

typedef	struct		s_player
{
	mlx_image_t*	img;
	int				x;
	int				y;
	int				walk_dir;
	int				turn_dir;
	double			rot_angle;
	double			rot_speed;
	double			move_speed;
}					t_player;

typedef	struct		s_data
{
	const char*		map;
	const char**	map_arr;
	mlx_t*			game;
	mlx_image_t*	wall;
	mlx_image_t*	space;
	mlx_image_t*	blank;
	t_player*		player;
	// mlx_image_t*	player;
	// int				player_x;
	// int				player_y;
}					t_data;