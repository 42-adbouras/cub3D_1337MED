/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:38 by adbouras          #+#    #+#             */
/*   Updated: 2024/12/24 17:20:28 by adbouras         ###   ########.fr       */
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

#define	WIDTH		1280
#define	HEIGHT		720
#define	TILE_SIZE	32

#define	WHITE		0xFFFFFFFF
#define BLACK		0x000000FF
#define RED			0xFF0000FF

typedef	struct		s_data
{
	const char*		map;
	mlx_t*			game;
	mlx_image_t*	wall;
	mlx_image_t*	space;
	mlx_image_t*	blank;
	mlx_image_t*	player;
	int				player_x;
	int				player_y;
}					t_data;