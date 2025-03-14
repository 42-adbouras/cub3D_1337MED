/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:58 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/13 10:17:55 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	key_press(t_data *data)
{
	data->player->turn_dir = 0;
	data->player->walk_dir = 0;
	data->player->strafe_dir = 0;
	if (mlx_is_key_down(data->game, MLX_KEY_ESCAPE))
		ft_exit(data, 0, GAME_EXIT, true);
	if (mlx_is_key_down(data->game, MLX_KEY_RIGHT))
		data->player->turn_dir = 1;
	if (mlx_is_key_down(data->game, MLX_KEY_LEFT))
		data->player->turn_dir = -1;
	if (mlx_is_key_down(data->game, MLX_KEY_W))
		data->player->walk_dir = 1;
	if (mlx_is_key_down(data->game, MLX_KEY_S))
		data->player->walk_dir = -1;
	if (mlx_is_key_down(data->game, MLX_KEY_D))
		data->player->strafe_dir = 1;
	if (mlx_is_key_down(data->game, MLX_KEY_A))
		data->player->strafe_dir = -1;
	if (mlx_is_key_down(data->game, MLX_KEY_LEFT_SHIFT))
		data->player->walk_dir *= 2.5;
}

void	draw_line(mlx_image_t *img, t_line line, uint32_t color)
{
	int		i;
	int		steps;
	double	x;
	double	y;

	line.delta_x = line.end_x - line.start_x;
	line.delta_y = line.end_y - line.start_y;
	if (abs(line.delta_x) > abs(line.delta_y))
		steps = abs(line.delta_x);
	else
		steps = abs(line.delta_y);
	line.x_inc = line.delta_x / (double)steps;
	line.y_inc = line.delta_y / (double)steps;
	x = line.start_x;
	y = line.start_y;
	i = -1;
	while (++i <= steps)
	{
		if (x >= 0 && x <= img->width && y >= 0 && y <= img->height)
			mlx_put_pixel(img, (int)round(x), (int)round(y), color);
		x += line.x_inc;
		y += line.y_inc;
	}
}

bool	if_collition(t_data *data, int32_t x, int32_t y)
{
	int		p_x;
	int		p_y;
	int		h_x;
	int		h_y;

	p_x = (x + data->player->x) / TILE_SIZE;
	p_y = (y + data->player->y) / TILE_SIZE;
	h_x = (x + data->player->x + HITBOX - 1) / TILE_SIZE;
	h_y = (y + data->player->y + HITBOX - 1) / TILE_SIZE;
	if (data->parsed_map[p_y][p_x] \
		!= '1' && data->parsed_map[h_y][h_x] != '1' \
		&& data->parsed_map[p_y][h_x] != '1' \
		&& data->parsed_map[h_y][p_x] != '1')
		return (true);
	return (false);
}

void	update_player_pose(t_data *data)
{
	double	move_step;
	double	straf_step;
	int32_t	new_x;
	int32_t	new_y;

	data->player->rot_angle += data->player->turn_dir * (data->rot_speed);
	data->player->rot_angle = norm_angle(data->player->rot_angle);
	move_step = data->player->walk_dir * (SPEED);
	straf_step = data->player->strafe_dir * (SPEED);
	new_x = round(cos(data->player->rot_angle) * move_step \
			- sin(data->player->rot_angle) * straf_step);
	new_y = round(sin(data->player->rot_angle) * move_step \
			+ cos(data->player->rot_angle) * straf_step);
	if (if_collition(data, new_x, new_y))
	{
		data->player->imge->instances->x += new_x;
		data->player->imge->instances->y += new_y;
	}
	data->player->x = data->player->imge->instances->x;
	data->player->y = data->player->imge->instances->y;
}

void	player_hook(t_data *data)
{
	key_press(data);
	update_player_pose(data);
}
