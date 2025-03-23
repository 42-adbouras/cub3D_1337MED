/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:48:30 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/19 10:40:43 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	minimap_bonus(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	draw_minimap_bonus(data);
}

void	draw_minimap_bonus(t_data *data)
{
	t_mini_map	m;

	m.y = 0;
	m.start_x = data->player->x - (MINI_WIDTH / 2) / M_MAP_FACT;
	m.start_y = data->player->y - (MINI_HEIGHT / 2) / M_MAP_FACT;
	while (m.y < MINI_HEIGHT)
	{
		m.x = 0;
		while (m.x < MINI_WIDTH)
		{
			m.map_x = (m.start_x + m.x / M_MAP_FACT) / TILE_SIZE;
			m.map_y = (m.start_y + m.y / M_MAP_FACT) / TILE_SIZE;
			draw_minimap_walls(data, &m);
			draw_minimap_border(data, &m);
			m.x++;
		}
		m.y++;
	}
	draw_player_bonus(data);
}

void	draw_player_bonus(t_data *data)
{
	t_line	line;
	int		offset;
	int		x;
	int		y;

	line.start_x = MINI_WIDTH / 2;
	line.start_y = MINI_HEIGHT / 2;
	line.end_x = MINI_WIDTH / 2 + 8 * cos(data->player->rot_angle);
	line.end_y = MINI_HEIGHT / 2 + 8 * sin(data->player->rot_angle);
	x = MINI_WIDTH / 2;
	y = MINI_HEIGHT / 2;
	offset = -2;
	while (offset <= 2)
	{
		mlx_put_pixel(data->minimap, x + offset, y, RED);
		mlx_put_pixel(data->minimap, x, y + offset, RED);
		offset++;
	}
	draw_line_bonus(data->minimap, line, RED);
}
