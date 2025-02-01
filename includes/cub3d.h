/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:38 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/01 18:50:45 by adbouras         ###   ########.fr       */
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

#define WIDTH			1440
#define HEIGHT			900
#define TILE_SIZE		42
#define MAP_FACT		0.2
#define HITBOX			4
#define SPEED			2
#define ROT_SPEED		3
#define FOV				80
#define RAYS			WIDTH
#define MOUSE_SENS		1000.00
#define NUM_SPRITES		18


#define MINI_MAP_WIDTH	350
#define MINI_MAP_HEIGHT	200
#define M_MAP_FACT		0.3

#define WHITE			0xFFFFFFFF
#define BLACK			0x000000FF
#define RED				0xFF0000FF
#define GREEN			0x00FF00FF

typedef	struct			s_sprite
{
	char**				path;
	mlx_texture_t*		s_texture[NUM_SPRITES];
	mlx_image_t*		s_images[NUM_SPRITES];
}						t_sprite;

typedef	struct			s_line
{
	int					start_x;
	int					start_y;
	int					end_x;
	int					end_y;
	int					delta_x;
	int					delta_y;
	double				x_inc;
	double				y_inc;
}						t_line;

typedef	struct			s_mini_map
{
	int					x;
	int					y;
	int					map_x;
	int					map_y;
	int					start_x;
	int					start_y;
}						t_mini_map;

typedef	struct			s_player
{
	mlx_image_t*		imge;
	mlx_image_t*		rays;
	int					x;
	int					y;
	int					walk_dir;
	int					turn_dir;
	int					strafe_dir;
	double				rot_angle;
}						t_player;

typedef	struct			s_ray
{
	double				angle;
	double				distance;
	bool				h_cross;
	bool				v_cross;
	double				wall_hit_x;
	double				wall_hit_y;
	bool				face_up;
	bool				face_down;
	bool				face_left;
	bool				face_right;
	bool				is_hori;
}						t_ray;

typedef	struct			s_text
{
	double				angle;
	double				distance;
	bool				h_cross;
	bool				v_cross;
	double				wall_hit_x;
	double				wall_hit_y;
	bool				face_up;
	bool				face_down;
	bool				face_left;
	bool				face_right;
	bool				is_hori;
}						t_text;

typedef	struct			s_data
{
	const char*			map;
	char**				map_arr;
	char				**parsed_map;
	char*				north_texture;
	char*				south_texture;
	char*				west_texture;
	char*				east_texture;
	int					floor_color[3];
	int					ceiling_color[3];
	int					map_width;
	int					map_height;
	mlx_t*				game;
	mlx_image_t*		frame;
	mlx_image_t*		minimap;
	mlx_texture_t*		tx;
	mlx_image_t*		im;
	t_player*			player;
	t_ray*				ray;
	t_text				text[RAYS];
	t_sprite			sprites;
	double				rot_speed;
	double				fov;
}						t_data;

void	init_data(t_data *data, char *arg);
void	load_game(t_data **data);
void	get_player_position(t_data *data, int *x, int *y);
void	load_player(t_data **data);
void	load_images(t_data **data);
void	load_ray(t_data **data);

void	import_map(t_data **data, char *path);
void	draw_minimap(t_data	*data);
void	draw_player(t_data *data);
void	get_map_size(t_data *data);

void    draw_line(mlx_image_t *img, t_line line, uint32_t color);

void	player_hook(t_data *data);

double	norm_angle(double angle);

void	game_loop(void *param);
void	raycasting(t_data *data);
void	draw_bg(t_data *data);
void	render_strip(t_data *data, int ray, double distance);
void	draw_rect(t_data *data, double x, double y, double width, double height);
void	draw_walls(t_data *data);

int		rgba(int r, int g, int b, int a);

void	mouse_hook(t_data *data);

void	close_game(void *param);
void	ft_exit(t_data *data, int i, bool term);
void	free_char_arr(char **arr);
int		parse_map(t_data *data);
char	**ft_split_cub(char const *s, char c);

void	load_sprites(t_data *data);
void	animation(t_data *data);
