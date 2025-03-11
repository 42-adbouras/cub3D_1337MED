/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:55:15 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/11 15:03:01 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

double	door_dist(t_data *data, double ray_x, double ray_y)
{
	return (sqrt(pow(ray_x - data->player->x, 2) \
		+ pow(ray_y - data->player->y, 2)));
}

void	door_handle(t_data *data)
{
	double	ray_angle;
	int		map_x;
	int		map_y;
	t_door	door;

	ray_angle = data->player->rot_angle;
	door.ray_x = data->player->x;
	door.ray_y = data->player->y;
	door.step_x = cos(ray_angle);
	door.step_y = sin(ray_angle);
	door.hit = false;
	while (!door.hit && door_dist(data, door.ray_x, door.ray_y) < TILE_SIZE * 2)
	{
		door.ray_x += door.step_x;
		door.ray_y += door.step_y;
		map_x = (int)(door.ray_x / TILE_SIZE);
		map_y = (int)(door.ray_y / TILE_SIZE);
		if (map_x < 0 || map_x >= data->map_width || map_y < 0 || map_y >= data->map_height)
			break ;
		if (data->parsed_map[map_y][map_x] == DOOR_CLOSED)
		{
			data->parsed_map[map_y][map_x] = DOOR_OPENED;
			door.hit = true;
		}
		else if (data->parsed_map[map_y][map_x] == DOOR_OPENED \
			&& data->parsed_map[data->player->y / TILE_SIZE][data->player->x / TILE_SIZE] != DOOR_OPENED)
		{
			data->parsed_map[map_y][map_x] = DOOR_CLOSED;
			door.hit = true;
		}
	}
}

void	door_key(t_data *data)
{
	static bool	door_key;

	if (mlx_is_key_down(data->game, MLX_KEY_E))
	{
		if (!door_key)
		{
			door_handle(data);
			door_key = true;
		}
	}
	else
		door_key = false;
}
