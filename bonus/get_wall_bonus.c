/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:39:24 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/16 12:57:36 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	assigne_hori_walls_bonus(t_data *data, double ray_angle, int ray)
{
	int	map_x;
	int	map_y;

	map_x = floor(data->text[ray].wall_hit_x / TILE_SIZE);
	map_y = floor(data->text[ray].wall_hit_y / TILE_SIZE);
	if (data->text[ray].face_up)
		map_y--;
	if (map_y >= 0 && map_y < data->map_height \
		&& map_x >= 0 && map_x < data->map_width \
		&& map_x < (int)ft_strlen(data->parsed_map[map_y]))
		data->text[ray].contant = data->parsed_map[map_y][map_x];
	if (sin(ray_angle) > 0)
		data->text[ray].wall_facing = SOUTH;
	else
		data->text[ray].wall_facing = NORTH;
}

void	assigne_vert_walls_bonus(t_data *data, double ray_angle, int ray)
{
	int	map_x;
	int	map_y;

	map_x = floor(data->text[ray].wall_hit_x / TILE_SIZE);
	map_y = floor(data->text[ray].wall_hit_y / TILE_SIZE);
	if (data->text[ray].face_left)
		map_x--;
	if (map_y >= 0 && map_y < data->map_height \
		&& map_x >= 0 && map_x < data->map_width \
		&& map_x < (int)ft_strlen(data->parsed_map[map_y]))
		data->text[ray].contant = data->parsed_map[map_y][map_x];
	if (cos(ray_angle) > 0)
		data->text[ray].wall_facing = EAST;
	else
		data->text[ray].wall_facing = WEST;
}
