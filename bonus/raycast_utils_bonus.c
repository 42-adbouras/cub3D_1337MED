/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 16:59:58 by adbouras          #+#    #+#             */
/*   Updated: 2025/02/27 17:42:04 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

bool	wall_at_bonus(t_data *data, int x, int y, int ray)
{
	int	map_x;
	int	map_y;

	if (!data->orient)
	{
		if (data->text[ray].face_left)
			x--;
	}
	else
	{
		if (data->text[ray].face_up)
			y--;
	}
	if (x < 0 || x >= data->map_width * TILE_SIZE \
		|| y < 0 || y >= data->map_height * TILE_SIZE)
		return (true);
	map_y = y / TILE_SIZE;
	map_x = x / TILE_SIZE;
	if (map_y >= data->map_height || map_x >= data->map_width)
		return (true);
	if (map_x >= (int)ft_strlen(data->parsed_map[map_y]))
		return (true);
	if (data->parsed_map[map_y][map_x] == '1')
	{
		data->text[ray].contant = '1';
		return (true);
	}
	if (data->parsed_map[map_y][map_x] == 'C')
	{
		data->text[ray].contant = 'C';
		return (true);	
	}
	return (false);
}

void	set_orientation_bonus(t_data *data, double angle, int ray)
{
	data->text[ray].face_down = (angle > 0 && angle < M_PI);
	data->text[ray].face_up = !data->text[ray].face_down;
	data->text[ray].face_right = (angle < 0.5 * M_PI || angle > 1.5 * M_PI);
	data->text[ray].face_left = !data->text[ray].face_right;
}

double	get_distance_bonus(double start_x, double start_y, double end_x, double end_y)
{
	return (sqrt(pow(end_x - start_x, 2) + pow(end_y - start_y, 2)));
}
