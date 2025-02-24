/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:38 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/24 12:54:04 by adbouras         ###   ########.fr       */
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

#define WIDTH			1366
#define HEIGHT			720
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

#define EAST  0
#define WEST  1
#define NORTH 2
#define SOUTH 3

typedef struct s_ray_utils
{
	double				x_step;
	double				y_step;
	double				x_inter;
	double				y_inter;
	double				next_x;
	double				next_y;
	int					player_x;
	int					player_y;
}						t_ray_utils;

typedef struct s_line
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

typedef struct s_player
{
	mlx_image_t			*imge;
	mlx_image_t			*rays;
	int					x;
	int					y;
	int					walk_dir;
	int					turn_dir;
	int					strafe_dir;
	double				rot_angle;
}						t_player;

typedef struct s_xy
{
	double				x;
	double				y;
}	t_xy;

typedef struct s_text
{
	mlx_texture_t		*img;
	double				angle;
	double				distance;
	int					wall_facing;
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

typedef struct s_texture
{
	mlx_texture_t		*north_img;
	mlx_texture_t		*south_img;
	mlx_texture_t		*west_img;
	mlx_texture_t		*east_img;
}	t_texture;

typedef struct s_data
{
	const char			*map;
	char				**map_arr;
	char				**parsed_map;
	char				*north_texture;
	char				*south_texture;
	char				*west_texture;
	char				*east_texture;
	int					floor_color[3];
	int					ceiling_color[3];
	int					map_width;
	int					map_height;
	mlx_t				*game;
	t_texture			*texture;
	mlx_image_t			*frame;
	mlx_image_t			*minimap;
	mlx_texture_t		*p_txtre;
	mlx_image_t			*p_asset;
	t_player			*player;
	t_text				text[RAYS];
	double				rot_speed;
	double				fov;
	bool				orient;
}						t_data;

void	init_data(t_data *data, char *arg);
void	load_game(t_data *data);
void	get_player_position(t_data *data, int *x, int *y);
void	load_player(t_data *data);
void	load_images(t_data *data);
void	load_ray(t_data *data);

void	import_map(t_data *data, char *path);
void	get_map_size(t_data *data);

void	draw_line(mlx_image_t *img, t_line line, uint32_t color);

void	player_hook(t_data *data);

double	norm_angle(double angle);

void	game_loop(void *param);
void	raycasting(t_data *data);
void	draw_bg(t_data *data);
void	render_strip(t_data *data, int ray, double distance);
void	draw_rect(t_data *data, double x, double y, double height);
void	draw_walls(t_data *data);

int		rgba(int r, int g, int b, int a);

void	close_game(void *param);
void	ft_exit(t_data *data, int i, bool term);
void	free_char_arr(char **arr);
void	parse_map(t_data *data);
char	**ft_split_cub(char const *s, char c);

double	get_distance(double start_x, double start_y,
			double end_x, double end_y);
void	set_orientation(t_data *data, double angle, int ray);
bool	wall_at(t_data *data, int x, int y, int ray);
int		rgba(int r, int g, int b, int a);
void	parse_color(t_data *data, char *line, int id[]);
int		skip_spaces(const char *line, int i);
void	check_elements(t_data *data, char *line, int id[]);
int		count_rows(char **map, int i);
int		only_spaces(char	*line);
int		isspace(int c);
void	print_error(char *error);
void	check_map(char **map);
bool	is_bordered_map_char(char c);
bool	is_surrounded_by_spaces(int i, int j, char **map);
bool	is_on_border(int i, int j, int row_count, char **map);
void	which_texture(t_data	*data, int ray);
char	**extract_map_content(char **map_arr);
void	check_invalid_character(char c);
void	call_func(int id[], t_data	*data, int j, int *flag);
void	check_missing_elements(int id[], int size);
void	handle_map_parsing(t_data *data, int i);
void	load_textures(t_data *data);