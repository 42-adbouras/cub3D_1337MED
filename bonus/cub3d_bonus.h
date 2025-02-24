/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:42:38 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/24 10:33:51 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../libraries/MLX42/include/MLX42/MLX42.h"
#include "../libraries/libft/libft.h"
#include "get_next_line_bonus.h"

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

typedef struct s_sprite
{
	char				**path;
	mlx_texture_t		*s_texture[NUM_SPRITES];
	mlx_image_t			*s_images[NUM_SPRITES];
}						t_sprite;

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

typedef struct s_mini_map
{
	int					x;
	int					y;
	int					map_x;
	int					map_y;
	int					start_x;
	int					start_y;
}						t_mini_map;

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

typedef struct	s_texture
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
	mlx_texture_t		*tx;
	mlx_image_t			*im;
	t_player			*player;
	t_text				text[RAYS];
	t_sprite			sprites;
	double				rot_speed;
	double				fov;
	bool				orient;
	bool				animation;
}						t_data;

void	init_data_bonus(t_data *data, char *arg);
void	load_game_bonus(t_data *data);
void	get_player_position_bonus(t_data *data, int *x, int *y);
void	load_player_bonus(t_data *data);
void	load_images_bonus(t_data *data);
void	load_ray_bonus(t_data *data);

void	import_map_bonus(t_data *data, char *path);
void	draw_minimap_bonus(t_data	*data);
void	draw_player_bonus(t_data *data);
void	get_map_size_bonus(t_data *data);

void	draw_line_bonus(mlx_image_t *img, t_line line, uint32_t color);

void	player_hook_bonus(t_data *data);

double	norm_angle_bonus(double angle);

void	game_loop_bonus(void *param);
void	raycasting_bonus(t_data *data);
void	draw_bg_bonus(t_data *data);
void	render_strip_bonus(t_data *data, int ray, double distance);
// void	draw_rect_bonus(t_data *data, double x, double y, double width, double height, int ray, double texture_x);
void	draw_walls_bonus(t_data *data);

int		rgba(int r, int g, int b, int a);

void	mouse_hook_bonus(t_data *data);

void	close_game_bonus(void *param);
void	ft_exit_bonus(t_data *data, int i, bool term);
void	free_char_arr_bonus(char **arr);
void	parse_map_bonus(t_data *data);
char	**ft_split_cub(char const *s, char c);

void	load_sprites_bonus(t_data *data);
void	animation_bonus(t_data *data);

double	get_distance_bonus(double start_x, double start_y,
			double end_x, double end_y);
void	set_orientation_bonus(t_data *data, double angle, int ray);
bool	wall_at_bonus(t_data *data, int x, int y, int ray);
int		rgba(int r, int g, int b, int a);

void	load_textures_bonus(t_data *data);
void	parse_color_bonus(t_data *data, char *line, int id[]);
int		skip_spaces_bonus(const char *line, int i);
void	check_elements_bonus(t_data *data, char *line, int id[]);
int		count_rows_bonus(char **map, int i);
int		only_spaces_bonus(char	*line);
int		isspace_bonus(int c);
void	print_error_bonus(char *error);
void	check_map_bonus(char **map);
bool	is_bordered_map_char_bonus(char c);
bool	is_surrounded_by_spaces_bonus(int i, int j, char **map);
bool	is_on_border_bonus(int i, int j, int row_count, char **map);
void	which_texture_bonus(t_data	*data, int ray);
char	**extract_map_content_bonus(char **map_arr);
void	check_invalid_character_bonus(char c);
void	call_func_bonus(int id[], t_data	*data, int j, int *flag);
void	check_missing_elements_bonus(int id[], int size);
void	handle_map_parsing_bonus(t_data *data, int i);
void	which_texture_bonus(t_data	*data, int ray);
void	render_strip_bonus(t_data *data, int ray, double distance);
void	draw_rect_bonus(t_data *data, double x, double y, double height);
