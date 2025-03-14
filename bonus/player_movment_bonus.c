/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:26:58 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/13 10:40:30 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	key_press_bonus(t_data *data)
{
	data->player->turn_dir = 0;
	data->player->walk_dir = 0;
	data->player->strafe_dir = 0;
	if (mlx_is_key_down(data->game, MLX_KEY_ESCAPE))
		ft_exit_bonus(data, 0, GAME_EXIT, false);
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
	if (mlx_is_mouse_down(data->game, MLX_MOUSE_BUTTON_LEFT))
		data->animation = true;
	door_key(data);
}

bool	if_collition_bonus(t_data *data, int32_t x, int32_t y)
{
	int		p_x;
	int		p_y;
	int		h_x;
	int		h_y;

	p_x = (x + data->player->x) / TILE_SIZE;
	p_y = (y + data->player->y) / TILE_SIZE;
	h_x = (x + data->player->x + HITBOX - 1) / TILE_SIZE;
	h_y = (y + data->player->y + HITBOX - 1) / TILE_SIZE;
	if (data->parsed_map[p_y][p_x] == '1' \
		|| data->parsed_map[h_y][h_x] == '1' \
		|| data->parsed_map[p_y][h_x] == '1' \
		|| data->parsed_map[h_y][p_x] == '1')
		return (true);
	if (data->parsed_map[p_y][p_x] == 'C' \
		|| data->parsed_map[h_y][h_x] == 'C' \
		|| data->parsed_map[p_y][h_x] == 'C' \
		|| data->parsed_map[h_y][p_x] == 'C')
		return (true);
	return (false);
}

void	update_player_pose_bonus(t_data *data)
{
	double	move_step;
	double	straf_step;
	int32_t	new_x;
	int32_t	new_y;

	data->player->rot_angle += data->player->turn_dir * (data->rot_speed);
	data->player->rot_angle = norm_angle_bonus(data->player->rot_angle);
	move_step = data->player->walk_dir * (SPEED);
	straf_step = data->player->strafe_dir * (SPEED);
	new_x = round(cos(data->player->rot_angle) * move_step \
			- sin(data->player->rot_angle) * straf_step);
	new_y = round(sin(data->player->rot_angle) * move_step \
			+ cos(data->player->rot_angle) * straf_step);
	if (!if_collition_bonus(data, new_x, new_y))
	{
		data->player->imge->instances->x += new_x;
		data->player->imge->instances->y += new_y;
	}
	data->player->x = data->player->imge->instances->x;
	data->player->y = data->player->imge->instances->y;
}

void	player_hook_bonus(t_data *data)
{
	key_press_bonus(data);
	update_player_pose_bonus(data);
}
