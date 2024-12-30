/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:45:49 by adbouras          #+#    #+#             */
/*   Updated: 2024/12/30 20:22:02 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	ft_key_hook(void *param)
{
	t_data	*data;

	data = (t_data*)param;
	if (mlx_is_key_down(data->game->window, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(data->game->window, MLX_KEY_W))
		data->player->walk_dir = 1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_S))
		data->player->walk_dir = -1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_D))
		data->player->strafe_dir = 1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_A))
		data->player->strafe_dir = -1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_RIGHT))
		data->player->turn_dir = 1;
	if (mlx_is_key_down(data->game->window, MLX_KEY_LEFT))
		data->player->turn_dir = -1;
	update_player_pos(data);
	data->player->turn_dir = 0;
	data->player->walk_dir = 0;
	data->player->strafe_dir = 0;
}

void	update_player_pos(t_data* data)
{
	double	step;
	double	straf_step;
	double	x;
	double	y;

	data->player->rot_angle += data->player->turn_dir * ROT_SPEED;
	step = data->player->walk_dir * SPEED;
	straf_step = data->player->strafe_dir * SPEED;

	x = cos(data->player->rot_angle) * step - sin(data->player->rot_angle) * straf_step;
	y = sin(data->player->rot_angle) * step + cos(data->player->rot_angle) * straf_step;

	// int		p_x = (int)roundf(x);
	// int		p_y = (int)roundf(y);

	// if (data->map_arr[p_y/32][p_x/32] != '1' && data->map_arr[(p_y + HITBOX - 1)/32][(p_x + HITBOX - 1)/32] != '1'
	// 	&& data->map_arr[p_y/32][(p_x + HITBOX - 1)/32] != '1' && data->map_arr[(p_y + HITBOX - 1)/32][p_x/32] != '1')
	// {
	// 	data->player->img->instances->x = p_x;
	// 	data->player->img->instances->y = p_y;
	// }
	if_collition(data, x, y);
}

void	if_collition(t_data *data, double x, double y)
{
	int		p_x = (int)roundf(x + data->player->img->instances->x);
	int		p_y = (int)roundf(y + data->player->img->instances->y);
	int		h_x = (p_x + HITBOX - 1) / 32;
	int		h_y = (p_y + HITBOX - 1) / 32;

	if (data->map_arr[p_y / 32][p_x / 32] != '1' && data->map_arr[h_y][h_x] != '1'
		&& data->map_arr[p_y / 32][h_x] != '1' && data->map_arr[h_y][p_x / 32] != '1')
	{
		data->player->img->instances->x = p_x;
		data->player->img->instances->y = p_y;
	}
}