/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbouras <adbouras@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:48:30 by adbouras          #+#    #+#             */
/*   Updated: 2025/03/11 17:16:33 by adbouras         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	draw_minimap_walls(t_data *data, t_mini_map *m)
{
	char	map_char;

	if (m->map_y < 0 || m->map_x < 0 || m->map_y >= data->map_height \
		|| m->map_x >= (int)ft_strlen(data->parsed_map[m->map_y]))
	{
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 180));
		return ;
	}
	map_char = data->parsed_map[m->map_y][m->map_x];
	if (map_char == '1')
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 180));
	else if (map_char == 'C')
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 255));
	else if (map_char == 'O')
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 50));
	else if (map_char == '0')
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(36, 28, 45, 200));
	else
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 180));
}

void	draw_minimap_border(t_data *data, t_mini_map *m)
{
	if ((m->x >= 0 && m->x < 4) || (m->y >= 0 && m->y < 4) \
		|| (m->x >= MINI_WIDTH - 4 && m->x <= MINI_WIDTH) \
		|| (m->y >= MINI_HEIGHT - 4 && m->y <= MINI_HEIGHT))
		mlx_put_pixel(data->minimap, m->x, m->y, rgba(230, 230, 230, 255));
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
	t_line		line;

	line.start_x = MINI_WIDTH / 2;
	line.start_y = MINI_HEIGHT / 2;
	line.end_x = MINI_WIDTH / 2 + 10 * cos(data->player->rot_angle);
	line.end_y = MINI_HEIGHT / 2 + 10 * sin(data->player->rot_angle);
	mlx_put_pixel(data->minimap, (MINI_WIDTH / 2), (MINI_HEIGHT / 2), RED);
	mlx_put_pixel(data->minimap, (MINI_WIDTH / 2) + 1, (MINI_HEIGHT / 2), RED);
	mlx_put_pixel(data->minimap, (MINI_WIDTH / 2) - 1, (MINI_HEIGHT / 2), RED);
	mlx_put_pixel(data->minimap, (MINI_WIDTH / 2), (MINI_HEIGHT / 2) + 1, RED);
	mlx_put_pixel(data->minimap, (MINI_WIDTH / 2), (MINI_HEIGHT / 2) - 1, RED);
	mlx_put_pixel(data->minimap, (MINI_WIDTH / 2) + 2, (MINI_HEIGHT / 2), RED);
	mlx_put_pixel(data->minimap, (MINI_WIDTH / 2) - 2, (MINI_HEIGHT / 2), RED);
	mlx_put_pixel(data->minimap, (MINI_WIDTH / 2), (MINI_HEIGHT / 2) + 2, RED);
	mlx_put_pixel(data->minimap, (MINI_WIDTH / 2), (MINI_HEIGHT / 2) - 2, RED);
}
